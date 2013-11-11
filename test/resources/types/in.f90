module TypesMod
  use iso_c_binding
  implicit none
  public


  type, public :: TypesType
  private
    real a
    real :: b
    real, public :: c
  contains

  end type TypesType

  public :: Types

contains

  subroutine Types() bind(c, name="Types")
    integer :: a
    integer b
    integer :: c

    c = b + a

  end subroutine Types

end module TypesMod
