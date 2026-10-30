// Temporary, hash-checked, in-memory Ghidra decompilation of native 2884B
// particle Update whose original vtable target lacks a function record.
// Do NOT persist metadata changes or modify original executable bytes.
//@author th20-reconstruction
//@category TH20
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;
import java.io.File;
import java.io.PrintWriter;
import java.security.MessageDigest;
import java.util.HexFormat;

public class RecoverParticleUpdate extends GhidraScript {
  private static final String BODY_SHA256="0d8c82a2018031e59c5e7172e08318e133f3513b6fc4639a1bab506c41eb02d1";
  @Override protected void run() throws Exception {
    String[] args=getScriptArgs();
    if(args.length != 1) throw new IllegalArgumentException("Expected one output path");
    Address head=toAddr("0x0045C360");
    Address end=toAddr("0x0045CEA3");
    byte[] bytes=new byte[2884];currentProgram.getMemory().getBytes(head,bytes);
    String digest=HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(bytes));
    if(!BODY_SHA256.equals(digest)) throw new IllegalStateException("original 2884B hash mismatch");
    byte[] alignment=new byte[12]; currentProgram.getMemory().getBytes(toAddr("0x0045CEA4"),alignment);
    for(byte value:alignment) if(value!=(byte)0xCC) throw new IllegalStateException("original INT3 mismatch");
    int transaction=currentProgram.startTransaction("TEMP-TH20-2884-in-memory-only");
    try {
      Function existing=getFunctionAt(head);
      if(existing!=null)throw new IllegalStateException("unexpected preexisting function at native head");
      // The original 2884B span and ret are independently PE/Capstone proven.
      // The function is created only in this ephemeral transaction.
      disassemble(head);
      Function recovered=currentProgram.getFunctionManager().createFunction(
          "provisional_2884_particle_update",head,new AddressSet(head,end),SourceType.ANALYSIS);
      if(recovered==null)throw new IllegalStateException("could not create temporary function");
      DecompInterface decompiler=new DecompInterface();
      decompiler.toggleCCode(true);decompiler.toggleSyntaxTree(true);
      if(!decompiler.openProgram(currentProgram))throw new IllegalStateException(decompiler.getLastMessage());
      try {
        DecompileResults result=decompiler.decompileFunction(recovered,300,monitor);
        if(!result.decompileCompleted())throw new IllegalStateException(result.getErrorMessage());
        try(PrintWriter output=new PrintWriter(new File(args[0]),"UTF-8")) {
          output.println("// TEMPORARY DECOMPILATION ONLY, ORIGINAL 2884B PE VERIFIED, NOT EXACT SOURCE");
          output.println("// Original SHA256 "+BODY_SHA256);
          output.println(result.getDecompiledFunction().getC());
        }
      } finally {decompiler.dispose();}
      println("TH20_TEMP_PARTICLE2884_DECOMPILE_OK");
    } finally {
      currentProgram.endTransaction(transaction,false);
    }
  }
}
