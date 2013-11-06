module SimpleSubroutineMod
  use iso_c_binding
  implicit none

  public :: SimpleSubroutine

contains

  subroutine SimpleSubroutine() bind(c, name="SimpleSubroutine")
    integer :: a
    integer b
    integer :: c

    c = b + a

  end subroutine SimpleSubroutine

end module SimpleSubroutineMod
