//! Rust wrapper of the `myta` C library.
//!
//! [`ffi`] holds the raw declarations of the C API, the rest of the crate is its
//! safe counterpart.

use std::fmt;

pub mod ffi;

/// Error code returned by the C library
#[derive(Clone, Copy, PartialEq, Eq)]
pub struct Error(pub u32);

impl fmt::Debug for Error {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "Error({:#x})", self.0)
    }
}

impl fmt::Display for Error {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "myta error {:#x}", self.0)
    }
}

impl std::error::Error for Error {}

pub type Result<T> = std::result::Result<T, Error>;

fn check(code: u32) -> Result<()> {
    if code == 0 {
        Ok(())
    } else {
        Err(Error(code))
    }
}

/// Session with the Trusted Application, closed when dropped
pub struct Session {
    handle: *mut ffi::myta_t,
}

// SAFETY: the session owns its handle and the C library has no thread-local state
unsafe impl Send for Session {}

impl Session {
    /// Connect to the TEE and open a session on the Trusted Application
    pub fn open() -> Result<Self> {
        let mut handle = std::ptr::null_mut();
        // SAFETY: `handle` is valid for the C library to store the new handle in
        check(unsafe { ffi::myta_open(&mut handle) })?;
        Ok(Self { handle })
    }

    /// Ask the Trusted Application to increment `value`, returns the new value
    pub fn inc_value(&mut self, mut value: u32) -> Result<u32> {
        // SAFETY: the handle is open and `value` is valid for reads and writes
        check(unsafe { ffi::myta_inc_value(self.handle, &mut value) })?;
        Ok(value)
    }
}

impl Drop for Session {
    fn drop(&mut self) {
        // SAFETY: the handle comes from `myta_open` and is closed only once
        unsafe { ffi::myta_close(self.handle) }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn error_display() {
        assert_eq!(Error(0xffff0006).to_string(), "myta error 0xffff0006");
    }
}
