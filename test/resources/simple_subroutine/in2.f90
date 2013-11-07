module SimpleSubroutineMod
  use iso_c_binding
  implicit none

  public :: SimpleSubroutine1
  public :: SimpleSubroutine2

contains

  subroutine SimpleSubroutine1() bind(c, name="SimpleSubroutine1")
    integer :: a
    integer b
    integer :: c

    c = b + a

  end subroutine SimpleSubroutine1


  subroutine SimpleSubroutine2() bind(c, name="SimpleSubroutine2")
  end subroutine SimpleSubroutine2

end module SimpleSubroutineMod
