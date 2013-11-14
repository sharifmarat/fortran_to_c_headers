module ArraysMod
  use iso_c_binding
  implicit none

  public :: Arrays

contains
  pure integer function GetArraySize()
    GetArraySize = 5
  end function GetArraySize

  subroutine Arrays(int1, double1, double2, int2) bind(c, name="Arrays")
    integer(kind=c_int)        :: int1(10)
    real*8, intent(in), dimension(10, GetArraySize(), *)  :: double1
    real*8, intent(in), dimension(10, 20, *)              :: double2
    integer             :: int2(:), int5, int6(4)

    intent(in) :: int1, int2

  end subroutine Arrays

end module ArraysMod

