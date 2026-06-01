#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to benchmark_msg__msg__BenchmarkParams

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BenchmarkParams {

    // This member is not documented.
    #[allow(missing_docs)]
    pub enable_adaptative: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub full_payload: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mu: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mu_zone1: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mu_zone2: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub mu_zone3: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub new_vel_max: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub new_w_max: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub dist_obst: f64,

}



impl Default for BenchmarkParams {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::BenchmarkParams::default())
  }
}

impl rosidl_runtime_rs::Message for BenchmarkParams {
  type RmwMsg = super::msg::rmw::BenchmarkParams;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        enable_adaptative: msg.enable_adaptative,
        full_payload: msg.full_payload,
        mu: msg.mu,
        mu_zone1: msg.mu_zone1,
        mu_zone2: msg.mu_zone2,
        mu_zone3: msg.mu_zone3,
        new_vel_max: msg.new_vel_max,
        new_w_max: msg.new_w_max,
        dist_obst: msg.dist_obst,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      enable_adaptative: msg.enable_adaptative,
      full_payload: msg.full_payload,
      mu: msg.mu,
      mu_zone1: msg.mu_zone1,
      mu_zone2: msg.mu_zone2,
      mu_zone3: msg.mu_zone3,
      new_vel_max: msg.new_vel_max,
      new_w_max: msg.new_w_max,
      dist_obst: msg.dist_obst,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      enable_adaptative: msg.enable_adaptative,
      full_payload: msg.full_payload,
      mu: msg.mu,
      mu_zone1: msg.mu_zone1,
      mu_zone2: msg.mu_zone2,
      mu_zone3: msg.mu_zone3,
      new_vel_max: msg.new_vel_max,
      new_w_max: msg.new_w_max,
      dist_obst: msg.dist_obst,
    }
  }
}


