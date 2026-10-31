// Original Card start's complete native typed capture payload.
// An implicit ordinary std::pmr::string copy constructor produces the
// separate 167-byte original STL copy head and original EH/cookie roles.
#include "NativeCardTextPayload.hpp"
#include "Card.hpp"
#include "Animation.hpp"
namespace th20 {
NativeCardTextPayload::NativeCardTextPayload(
    Card* owner, const std::pmr::string& source, Animation* ani)
    : card(owner), text(source), animation(ani) {}
NativeCardTextPayload::~NativeCardTextPayload() {}
}
