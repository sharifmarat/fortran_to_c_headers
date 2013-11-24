module BindVarsMod
  use iso_c_binding
  implicit none

  real*8, bind(c), parameter  :: dbl1 = 1.0d0
  real(kind=c_double), bind(c, name="dbl2"), parameter  :: dbl2 = 1.0d0
  integer(kind=c_int), bind(c, name="int1")  :: int1
  type(c_ptr), bind(c, name="ptr1") :: ptr1

contains

end module BindVarsMod

