#include <org.hpp>

  ACTION org::init (name checks_contract) {
    require_auth(get_self());
    settings_table _settings( get_self(), get_self().value );
    auto itr = _settings.find(1);
    if(itr == _settings.end()) {
      _settings.emplace(get_self(), [&](auto& row) {
        row.id = 1;
        row.checks_contract = checks_contract;
      });
    } else {
      _settings.modify(itr, get_self(),[&](auto& row) {
        row.checks_contract = checks_contract;
      });
    }

  }

  ACTION org::createsimple (name creator, name badge, vector<name> parentbadge, string ipfsimage, string details) {
    require_auth(creator);

    action {
      permission_level{get_self(), name("active")},
      checkscontract(),
      name("cschecks"),
      createsimple_args {
        .org = get_self(),
        .badge = badge,
        .parentbadge = parentbadge,
        .ipfsimage = ipfsimage,
        .details = details }
    }.send();

    action {
      permission_level{get_self(), name("active")},
      name("profiles"),
      name("createsimple"),
      createsimple_args {
        .org = get_self(),
        .badge = badge,
        .parentbadge = parentbadge,
        .ipfsimage = ipfsimage,
        .details = details }
    }.send();
  }


  ACTION org::creategotcha (name creator, name badge, time_point_sec starttime, uint64_t cycle_length, uint8_t max_cap, string ipfsimage, string details) {
    require_auth(creator);
    
    action {
      permission_level{get_self(), name("active")},
      checkscontract(),
      name("cgchecks"),
      creategotcha_args {
        .org = get_self(),
        .badge = badge,
        .starttime = starttime,
        .cycle_length = cycle_length,
        .max_cap = max_cap,
        .ipfsimage = ipfsimage,
        .details = details }
    }.send();
    
    action {
      permission_level{get_self(), name("active")},
      name("profiles"),
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

  ACTION org::createrollup (name creator, name badge, vector<badge_count> rollup_criteria, string ipfsimage, string details) {
    require_auth(creator);

    action {
      permission_level{get_self(), name("active")},
      checkscontract(),
      name("crchecks"),
      createrollup_args {
        .org = get_self(),
        .badge = badge,
        .rollup_criteria = rollup_criteria,
        .ipfsimage = ipfsimage,
        .details = details }
    }.send();

    action {
      permission_level{get_self(), name("active")},
      name("profiles"),
      name("createrollup"),
      createrollup_args {
        .org = get_self(),
        .badge = badge,
        .rollup_criteria = rollup_criteria,
        .ipfsimage = ipfsimage,
        .details = details }
    }.send();
  }

  ACTION org::givegotcha (name badge, name from, name to, uint8_t amount, string memo ) {
    require_auth(from);
    
    action {
      permission_level{get_self(), name("active")},
      checkscontract(),
      name("ggchecks"),
      givegotcha_args {
        .org = get_self(),
        .badge = badge,
        .from = from,
        .to = to,
        .amount = amount,
        .memo = memo }
    }.send();

    action {
      permission_level{get_self(), name("active")},
      name("profiles"),
      name("givegotcha"),
      givegotcha_args {
        .org = get_self(),
        .badge = badge,
        .from = from,
        .to = to,
        .amount = amount,
        .memo = memo }
    }.send();

  }


  ACTION org::givesimple (name from, name to, name badge, string memo ) {
    require_auth(from);

    action {
      permission_level{get_self(), name("active")},
      checkscontract(),
      name("gschecks"),
      givesimple_args {
        .org = get_self(),
        .to = to,
        .badge = badge,
        .memo = memo }
    }.send();

    action {
      permission_level{get_self(), name("active")},
      name("profiles"),
      name("givesimple"),
      givesimple_args {
        .org = get_self(),
        .to = to,
        .badge = badge,
        .memo = memo }
    }.send();
  }


  ACTION org::takerollup (name actor, name badge) {
    require_auth(actor);

    action {
      permission_level{get_self(), name("active")},
      checkscontract(),
      name("trchecks"),
      rollup_args {
        .org = get_self(),
        .account = actor,
        .badge = badge}
    }.send();
    
    action {
      permission_level{get_self(), name("active")},
      name("profiles"),
      name("takerollup"),
      rollup_args {
        .org = get_self(),
        .account = actor,
        .badge = badge}
    }.send();
  }


