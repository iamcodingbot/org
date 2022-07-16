#include <eosio/eosio.hpp>
#include <eosio/system.hpp>

using namespace std;
using namespace eosio;

CONTRACT org : public contract {
  public:
    using contract::contract;
    struct badge_count {
      name badge;
      uint16_t count;
    };

  ACTION addrole(name member, name role, time_point starttime, time_point endtime);
  
  ACTION createsimple (name creator, name badge, vector<name> parentbadge, string ipfsimage, string details);
  ACTION creategotcha (name creator, name badge, time_point_sec starttime, uint64_t cycle_length, uint8_t max_cap, string ipfsimage, string details);
  ACTION createrollup (name creator, name badge, vector<badge_count> rollup_criteria, string ipfsimage, string details);
  ACTION givegotcha (name badge, name from, name to, uint8_t amount, string memo );
  ACTION givesimple (name from, name to, name badge, string memo );
  ACTION takerollup (name account, name badge);

  private:

    TABLE badge {
      name badge;
      name account;
    };


    TABLE members {
      name role;
      time_point starttime;
      time_point endtime;
      auto primary_key() const {return role.value; }
    };
    typedef multi_index<name("members"), members> members_table;

    void checkrole(name member, name role) {
      members_table _members( _self, member.value );
      auto itr = _members.require_find(role.value, "Not a valid role for this action");
      check(current_time_point() >= itr->starttime && current_time_point() <= itr->endtime, "role expired");
    }

    struct createsimple_args {
      name org;
      name badge;
      vector<name> parentbadge;
      string ipfsimage;
      string details;
    };

    struct creategotcha_args {
      name org;
      name badge;
      time_point_sec starttime;
      uint64_t cycle_length;
      uint8_t max_cap;
      string ipfsimage;
      string details;
    };

    struct createrollup_args {
      name org;
      name badge;
      vector<badge_count> rollup_criteria;
      string ipfsimage;
      string details;
    };

    struct claimgotcha_args {
      name org;
      name account; 
    };

    struct givegotcha_args {
      name org;
      name badge;
      name from;
      name to;
      uint8_t amount;
      string memo;
    };

    struct givesimple_args {
      name org;
      name to;
      name badge;
      string memo;
    };

    struct rollup_args {
      name org;
      name account;
      name badge;
    };

};
