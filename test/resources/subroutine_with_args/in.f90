module SubroutineWithArgsMod
  use iso_c_binding
  implicit none

  public :: SubroutineWithArgs

contains

  subroutine SubroutineWithArgs(int1, double1, int2) bind(c, name="SubroutineWithArgs")
    integer(kind=c_int), value :: int1
    real*8, intent(in)         :: double1
    integer, value             :: int2

    intent(in) :: int1, int2
    value double1

  end subroutine SubroutineWithArgs

end module SubroutineWithArgsMod

