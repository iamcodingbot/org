#include <org.hpp>

  ACTION org::addrole(name member, name role, time_point starttime, time_point endtime) {

    require_auth(get_self());
    members_table _members( _self, member.value );

    auto itr = _members.find(role.value);
    if(itr == _members.end()) {
      _members.emplace(get_self(), [&](auto& row) {
        row.role = name(role);
        row.starttime = starttime;
        row.endtime = endtime;
      });
    } else {
      _members.modify(itr, get_self(), [&](auto& row) {
        row.starttime = starttime;
        row.endtime = endtime;
      });
    }

  }

  ACTION org::createsimple (name creator, name badge, vector<name> parentbadge, string ipfsimage, string details) {
    require_auth(creator);
    
    checkrole(creator, name("hcd"));

    action {
      permission_level{get_self(), name("active")},
      name("profile"),
      name("createsimple"),
      createsimple_args {
        .org = get_self(),
        .badge = badge,
        .parentbadge = parentbadge,
        .ipfsimage = ipfsimage,
        .details = details }
    }.send();
  }


  ACTION org::creategotcha (name creator, name badge, time_point starttime, uint64_t cycle_length, uint8_t max_cap, string ipfsimage, string details) {
    require_auth(creator);
    
    checkrole(creator, name("hcd"));
    
    action {
      permission_level{get_self(), name("active")},
      name("profile"),
      name("creategotcha"),
      creategotcha_args {
        .org = get_self(),
        .badge = badge,
        .starttime = starttime,
        .cycle_length = cycle_length,
        .max_cap = max_cap,
        .ipfsimage = ipfsimage,
        .details = details }
    }.send();
  }


  ACTION org::claimgotcha (name claimer) {
    require_auth(claimer);
    
    checkrole(claimer, name("member"));
    
    action {
      permission_level{get_self(), name("active")},
      name("profile"),
      name("claimgotcha"),
      claimgotcha_args {
        .org = get_self(),
        .account = claimer }
    }.send();
  }

  ACTION org::givegotcha (name from, name to, uint8_t amount, string memo ) {
    require_auth(from);
    
    checkrole(from, name("member"));
    checkrole(to, name("member"));

    action {
      permission_level{get_self(), name("active")},
      name("profile"),
      name("givegotcha"),
      givegotcha_args {
        .org = get_self(),
        .from = from,
        .to = to,
        .amount = amount,
        .memo = memo }
    }.send();

  }


  ACTION org::givesimple (name from, name to, name badge, string memo ) {
    require_auth(from);

    checkrole(from, name("member"));

    action {
      permission_level{get_self(), name("active")},
      name("profile"),
      name("givesimple"),
      givesimple_args {
        .org = get_self(),
        .to = to,
        .badge = badge,
        .memo = memo }
    }.send();
  }


  ACTION org::rollup (name actor, name badge, vector<badge_count>& existing_badges) {
    require_auth(actor);

    checkrole(actor, name("member"));
    
    action {
      permission_level{get_self(), name("active")},
      name("profile"),
      name("rollup"),
      rollup_args {
        .org = get_self(),
        .account = actor,
        .badge = badge,
        .existing_badges = existing_badges }
    }.send();
  }


