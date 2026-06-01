#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "benchmark_msg__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__benchmark_msg__msg__BenchmarkParams() -> *const std::ffi::c_void;
}

#[link(name = "benchmark_msg__rosidl_generator_c")]
extern "C" {
    fn benchmark_msg__msg__BenchmarkParams__init(msg: *mut BenchmarkParams) -> bool;
    fn benchmark_msg__msg__BenchmarkParams__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<BenchmarkParams>, size: usize) -> bool;
    fn benchmark_msg__msg__BenchmarkParams__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<BenchmarkParams>);
    fn benchmark_msg__msg__BenchmarkParams__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<BenchmarkParams>, out_seq: *mut rosidl_runtime_rs::Sequence<BenchmarkParams>) -> bool;
}

// Corresponds to benchmark_msg__msg__BenchmarkParams
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !benchmark_msg__msg__BenchmarkParams__init(&mut msg as *mut _) {
        panic!("Call to benchmark_msg__msg__BenchmarkParams__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for BenchmarkParams {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { benchmark_msg__msg__BenchmarkParams__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { benchmark_msg__msg__BenchmarkParams__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { benchmark_msg__msg__BenchmarkParams__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for BenchmarkParams {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for BenchmarkParams where Self: Sized {
  const TYPE_NAME: &'static str = "benchmark_msg/msg/BenchmarkParams";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__benchmark_msg__msg__BenchmarkParams() }
  }
}


