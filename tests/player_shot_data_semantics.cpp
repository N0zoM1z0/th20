#include "Player.hpp"
#include "ShotData.hpp"
#include "Session.hpp"
#include "WeaponStoneInfo.hpp"
#define main unused_archive_fixture_main
#include "archive_owner_semantics.cpp"
#undef main
namespace th20 {
// Explicit unresolved interface bindings. Neither original owner destruction
// nor gameplay activation is accepted by this constructor/resource scope.
Player::~Player() {std::abort();}
void Player::enable() {std::abort();}
WeaponStoneInfo::~WeaponStoneInfo() {std::abort();}
void WeaponStoneInfo::enable() {std::abort();}
WeaponStoneInfo* fixture_overlay;
void DiagnosticAllocator::release_animation_callback(AnimationCallback* value) {assert(!value);}
const Matrix4 identity_matrix=[] {
    Matrix4 result;for (int i=0;i<4;++i)result.elements[i][i]=1;return result;
}();
}
void inspect_resource(th20::Player& player,const char* name) {
    using namespace th20;
    std::int32_t size=0;
    auto* original=read_game_resource(name,&size,0);assert(original && size>=0x5d4);
    auto* original_header=reinterpret_cast<PlayerShotData*>(original);
    PlayerShotData* loaded=nullptr;assert(player.load_shot_data(&loaded,name)==0 && loaded);
    assert(std::memcmp(original,loaded,sizeof(PlayerShotData))==0);
    for (int i=0;i<loaded->entry_count;++i) {
        auto raw=original_header->entry_offsets[i];
        auto expected=static_cast<std::int32_t>(raw)<0?raw:
            raw+static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(loaded));
        assert(loaded->entry_offsets[i]==expected);
    }
    player.shot_data=loaded;
    // The observed cap deliberately uses global Context zero even for a Player
    // selecting Context one. Verify both row getters and every column.
    player.view_index=1;player.context=&session.context(1);
    auto& record=session.table.players[0];
    for (int row10:{0,1,60,120}) for (int row14:{0,7,120})
        for (int phase:{-1,0,1,2}) for (unsigned focus:{0u,1u,2u,255u}) {
            record.field_10=row10;record.field_14=row14;
            fixture_overlay->phase=phase;player.focused=focus;
            int row=phase==1||focus?row10:row14;
            int column=phase==1?2:(focus?1:0);
            assert(player.damage_limit()==original_header->damage_caps[row][column]);
        }
    player.shot_data=nullptr;
    process_allocator->release_bytes(loaded);process_allocator->release_bytes(original);
}
int main() {
    using namespace th20;
    DiagnosticAllocator allocator;process_allocator=&allocator;
    // Actual complete constructors run in heap storage. Original owner
    // destructors abort if called, so this scope manually closes the accepted
    // child Animation/TaskInfo lifetimes before releasing the enclosing storage.
    auto* memory=::operator new(sizeof(Player));std::memset(memory,0xa5,sizeof(Player));
    auto* player=::new(memory) Player;
    assert(player->direction.value==0 && player->value_1484c.value==0);
    assert(player->field_14850==0xa5a5a5a5u);
    assert(!player->shot_data && !player->animation_file && !player->focused);
    for (auto& option:player->options.values) assert(!option.state && !option.context);
    for (auto& option:player->secondary_options.values) assert(!option.state && !option.context);
    for (auto& point:player->points_20fc.values) assert(!point.x && !point.y);
    for (auto& shot:player->shots.pool.slots) assert(!shot.state_14 && !shot.link.node);
    auto* overlay=::new(::operator new(sizeof(WeaponStoneInfo))) WeaponStoneInfo;
    assert(!overlay->phase && !overlay->context && overlay->counter.threshold==1500);
    fixture_overlay=overlay;session.context(0).overlay_owner=overlay;
    overlay->disable();session.context(0).current_player=&session.table.players[0];
    session.context(1).current_player=&session.table.players[1];
    std::vector<Member> original_shape;
    for (int asset=0;asset<2;++asset) {
        Bytes data(sizeof(PlayerShotData)+160*8,0);
        auto* header=reinterpret_cast<PlayerShotData*>(data.data());header->entry_count=160;
        for (int row=0;row<121;++row) for (int column=0;column<3;++column)
            header->damage_caps[row][column]=(asset+1)*10000+row*10+column;
        for (unsigned i=0;i<160;++i)header->entry_offsets[i]=sizeof(PlayerShotData)+160*4+i*4;
        original_shape.push_back({asset?"pl01.sht":"pl00.sht",data,true});
    }
    disk[L"Z:\\game\\fixture.dat"]=archive(original_shape);
    assert(archive_owner.open("fixture.dat"));
    inspect_resource(*player,"pl00.sht");inspect_resource(*player,"pl01.sht");
    PlayerShotData* failed=reinterpret_cast<PlayerShotData*>(std::uintptr_t(1));
    assert(player->load_shot_data(&failed,"missing.sht")==-1 && !failed);
    archive_owner.close();
    Bytes bytes(sizeof(PlayerShotData)+20,0);auto* header=reinterpret_cast<PlayerShotData*>(bytes.data());
    header->entry_count=4;header->entry_offsets[0]=0x80000000u;
    header->entry_offsets[1]=0xffffffffu;header->entry_offsets[2]=0;header->entry_offsets[3]=sizeof(PlayerShotData)+16;
    std::vector<Member> members={{"signed.sht",bytes,true},{"empty.sht",Bytes(sizeof(PlayerShotData),0),false}};
    disk[L"Z:\\game\\fixture.dat"]=archive(members);assert(archive_owner.open("fixture.dat"));
    PlayerShotData* signed_header=nullptr;assert(player->load_shot_data(&signed_header,"signed.sht")==0);
    assert(signed_header->entry_offsets[0]==0x80000000u && signed_header->entry_offsets[1]==0xffffffffu);
    auto base=static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(signed_header));
    assert(signed_header->entry_offsets[2]==base);
    assert(signed_header->entry_offsets[3]==base+sizeof(PlayerShotData)+16);
    process_allocator->release_bytes(signed_header);
    PlayerShotData* empty=nullptr;assert(player->load_shot_data(&empty,"empty.sht")==0 && empty->entry_count==0);
    process_allocator->release_bytes(empty);archive_owner.close();
    std::destroy_at(&player->animation);player->TaskInfo::~TaskInfo();::operator delete(player);
    overlay->TaskInfo::~TaskInfo();::operator delete(overlay);fixture_overlay=nullptr;
    std::puts("Whole Player construction, actual archive/SHT relocation and 384 synthetic damage-cap selections passed; signed sentinels, zero-count and missing-resource exits passed. Owner/ANM/Context startup bindings remain explicit fixtures.");
}
