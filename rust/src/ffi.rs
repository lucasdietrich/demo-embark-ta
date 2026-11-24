//! Raw declarations of the C API of the `myta` library, see `include/`.
//!
//! Prefer the safe wrappers of the crate root.

#![allow(non_camel_case_types)]

/// Connection to the Trusted Application, see `myta.h`
#[repr(C)]
pub struct myta_t {
    _data: [u8; 0],
    _marker: core::marker::PhantomData<(*mut u8, core::marker::PhantomPinned)>,
}

unsafe extern "C" {
    pub fn myta_open(handle: *mut *mut myta_t) -> u32;
    pub fn myta_close(handle: *mut myta_t);
    pub fn myta_inc_value(handle: *mut myta_t, value: *mut u32) -> u32;
}
