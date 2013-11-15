module InitializeMod
  use iso_c_binding
  implicit none

  public :: Initialize

  public :: my_kind
  integer, parameter :: my_kind = 10

contains

  subroutine Initialize(int1, double1, double2, int2) bind(c, name="Initialize")
    integer(kind=c_int), intent(in), value :: int1
    real(kind=c_ptr), intent(in), value    :: double1
    real(kind=c_ptr), intent(out)          :: double2
    integer(kind=c_int), intent(out)       :: int2

    real*8, parameter :: my_pi = 3.14d0

  end subroutine Initialize

end module InitializeMod

