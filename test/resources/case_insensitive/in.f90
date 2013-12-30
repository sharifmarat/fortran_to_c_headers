module CaseInsensitiveMod
  USE ISO_C_BINDING
  IMPLICIT NONE

  REAL(KIND=C_DOUBLE), BIND(C, NAME="dbl2")   :: DBL2_FORTRAN = 1.0D0
  REAL*8, BIND(C)  :: DBL1 = 1.0D0
  INTEGER(KIND=C_INT), BIND(C, NAME="int1")  :: int1_fortran
  type(c_ptr), bind(c, name="ptr1") :: PTR1_FORTRAN

cOntAiNs

  SUbRouTine BindNames1_fortran(int_in_FORTRAN, double_in_fortran, int_out_fortran) bind(C, nAme="BindNames1")
    integer(kind=c_INT), BIND(c, name="int_in"), VALUE, intent(in)       :: int_in_fortran
    REAL(kind=C_dOuBlE), BINd(c, name="double_in"), value, INTENT(in)    :: DOUBLE_IN_FORTRAN
    iNteGer(kind=C_INT), bIND(c, name="int_out"), intent(OUT)            :: INT_OUT_fortran
    INT_OUT_FORTRAN = 5 + (3./1.)
  END SUBROUTINE BINDNames1_FORTRAN

end module CaseInsensitiveMod

