module SubroutineWithArgsPtrMod
  use iso_c_binding
  implicit none

  public :: SubroutineWithArgsPtr

contains

  subroutine SubroutineWithArgsPtr(int1, double1, int2, ptr1) bind(c, name="SubroutineWithArgsPtr")
    integer(kind=c_int), value :: int1
    real*8, intent(in)         :: double1
    integer, value             :: int2
    type(c_ptr), value         :: ptr1

    intent(in) :: int1, int2
    value double1

  end subroutine SubroutineWithArgsPtr

end module SubroutineWithArgsPtrMod

