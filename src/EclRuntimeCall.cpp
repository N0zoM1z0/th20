#include "EclRuntime.hpp"
#include "EclDiagnostic.hpp"

// Payload indices intentionally retain the native word-addressing protocol.
#define ECL_INTEGER_ARGUMENT(ins, index) (reinterpret_cast<std::int32_t*>((ins)+1)[index])

namespace th20 {
int EclRuntime::call_into(EclRuntime* target,std::int32_t argument_skip,std::int32_t name_skip) {
    EclInstruction* ins=current();
    std::uint32_t descriptor_offset=ECL_INTEGER_ARGUMENT(ins,0)+argument_skip*4+4;
    std::int32_t previous_frame=0;
    std::int32_t original_pointer=target->stack.pointer_value();
    std::int32_t destination=original_pointer+16;
    if(!original_pointer) {
        target->stack.push(4,&previous_frame,0);
        destination=20;
    }
    for(std::int32_t index=argument_skip+1;index<ins->argument_count;
        ++index,descriptor_offset+=8,destination+=4) {
        if(reinterpret_cast<char*>(ins+1)[descriptor_offset]=='f' ||
           reinterpret_cast<char*>(ins+1)[descriptor_offset]=='g') {
            float value=consuming_float_value(index,reinterpret_cast<float*>(ins+1)[(descriptor_offset+4)/4]);
            if(reinterpret_cast<char*>(ins+1)[descriptor_offset+1]=='f')
                *reinterpret_cast<float*>(&target->stack.absolute(destination))=value;
            else
                *reinterpret_cast<std::int32_t*>(&target->stack.absolute(destination))=static_cast<std::int32_t>(value);
        } else {
            std::int32_t value=consuming_integer_value(index,ECL_INTEGER_ARGUMENT(ins,(descriptor_offset+4)/4));
            if(reinterpret_cast<char*>(ins+1)[descriptor_offset+1]=='f')
                *reinterpret_cast<float*>(&target->stack.absolute(destination))=static_cast<float>(value);
            else
                *reinterpret_cast<std::int32_t*>(&target->stack.absolute(destination))=value;
        }
    }
    destination=target->stack.pointer_value();
    // Reuse the saved frame word before pushing the four-word return record.
    if(original_pointer) {
        target->stack.pop(4,&previous_frame,0);
        target->stack.set_pointer(original_pointer);
        target->stack.absolute(original_pointer-4)=previous_frame;
    } else {
        target->stack.set_pointer(4);
    }
    {
        target->stack.push(4,&destination,0);
    }
    if(original_pointer) {
        target->stack.push(4,&time,0);
        target->stack.push(4,&position.offset,0);
        target->stack.push(4,&position.subroutine,0);
    } else {
        std::int32_t ended=-1;
        target->stack.push(4,&ended,0);
        target->stack.push(4,&ended,0);
        target->stack.push(4,&ended,0);
    }
    EclRuntime* saved=manager->current_runtime;
    manager->current_runtime=target;
    if(manager->loader_value()->activate(manager,reinterpret_cast<char*>(ins+1)+name_skip*4+4)) {
        ecl_diagnostic_hint(ecl_missing_subroutine_format,reinterpret_cast<char*>(ins+1)+name_skip*4+4);
        position.offset=-1;position.subroutine=-1;
        return -1;
    }
    // Native failure retains the target as current; only success restores it.
    manager->current_runtime=saved;
    return 0;
}
}
