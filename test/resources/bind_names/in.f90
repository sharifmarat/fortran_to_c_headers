module BindNamesMod
  use iso_c_binding
  implicit none

  real(kind=c_double), bind(c, name="dbl2")   :: dbl2_fortran = 1.0d0
  real*8, bind(c)  :: dbl1 = 1.0d0
  integer(kind=c_int), bind(c, name="int1")  :: int1_fortran
  type(c_ptr), bind(c, name="ptr1") :: ptr1_fortran

contains

  subroutine BindNames1_fortran(int_in_fortran, double_in_fortran, int_out_fortran) bind(c, name="BindNames1")
    integer(kind=c_int), bind(c, name="int_in"), value, intent(in)       :: int_in_fortran
    real(kind=c_double), bind(c, name="double_in"), value, intent(in)    :: double_in_fortran
    integer(kind=c_int), bind(c, name="int_out"), intent(out)            :: int_out_fortran
    int_out_fortran = 5 + (3./1.)
  end subroutine BindNames1_fortran

end module BindNamesMod

