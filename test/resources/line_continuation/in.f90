module LineContinuationMod
  use iso_c_binding
  implicit none

  public :: LineContinuation

contains

  ! our sub
  subroutine LineContinuation(int1, &       ! int1
                      double1, &    ! double1
                      int2) & ! int2
                      bind(c, name="LineContinuation") ! comments 2
    integer(kind=c_int), &  !< int 1
      value :: int1      !< int 1 !!!
    real*8, intent(in)         :: double1   !< int 2 !!!
    integer, value             :: int2      !< int 3

    ! attributes
    intent(in) :: int1, int2        !< attributes
    value double1                   !< attributes

  end subroutine LineContinuation

  ! subroutine 2
  ! subroutine LineContinuation(int1, &
  !                 double1, int2) bind(c, name="LineContinuation") ! comments 2
  !   integer(kind=c_int), value :: int1      !< int 1 !!!
  !   real*8, intent(in)         :: double1   !< int 2 !!!
  !   integer, value             :: int2      !< int 3

  !   ! attributes
  !   intent(in) :: int1, int2        !< attributes
  !   value double1                   !< attributes

  ! end subroutine LineContinuation

end module LineContinuationMod

