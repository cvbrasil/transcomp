/*T
   Concepts: KSP^solving a system of linear equations
   Processors: 1
T*/
#include <petscksp.h>
#include "SolverLinear.h"
#include <vector>
#include <iostream>
#include <math.h>

SolverLinear::SolverLinear(vector<vector<double> >Avec,vector<double>bvec,int nint)
{
  bool teste = 1;
  if(Avec.size()!=nint && bvec.size()!=nint)
  {
    teste = 0;
  }
  for(int i=0; i<nint; i++)
  {
    if(Avec[i].size()!=nint)
    {
      teste = 0;
    }
  }
  if(teste==1)
  {
    this->Avec = Avec;
    this->bvec = bvec;
    this->CampodeTemperaturas.resize(nint);
    this->nint = nint;
  }
  else
  {
    cout<<endl<<endl<<"Problema! Matriz e vetor não possuem dimensão solicitada!"<<endl<<endl;
  }
}
vector<double> SolverLinear::getCampodeTemperaturas()
{
  Vec            b;
  Vec            x;
  Mat            A;            /* linear system matrix */
  KSP            ksp;          /* linear solver context */
  PetscReal      norm;         /* norm of solution error */
  PetscInt       its;
  PetscInt       n = this->nint;
  PetscScalar    Valor[1];

  
  PetscOptionsGetInt(NULL,NULL,"-n",&n,NULL);


  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
         Compute the matrix and right-hand-side vector that define
         the linear system, Ax = b.
     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

  /*
     Create vectors.  Note that we form 1 vector from scratch and
     then duplicate as needed.
  */
  VecCreate(PETSC_COMM_WORLD,&x);
  PetscObjectSetName((PetscObject) x, "Solution");
  VecSetSizes(x,PETSC_DECIDE,n);
  VecSetFromOptions(x);
  VecDuplicate(x,&b);

  /*
     Create matrix.  When using MatCreate(), the matrix format can
     be specified at runtime.

     Performance tuning note:  For problems of substantial size,
     preallocation of matrix memory is crucial for attaining good
     performance. See the matrix chapter of the users manual for details.
  */
  MatCreate(PETSC_COMM_WORLD,&A);
  MatSetSizes(A,PETSC_DECIDE,PETSC_DECIDE,n,n);
  MatSetFromOptions(A);
  MatSetUp(A);
  /*
     Assemble matrix
  */
  /*
     Set right-hand-side vector.
  */
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      Valor[0] = this->Avec[i][j];
      MatSetValues(A,1,&i,1,&j,Valor,INSERT_VALUES);
    }
    Valor[0] = this->bvec[i];
    VecSetValues(b,1,&i,Valor,INSERT_VALUES);
  }
  MatAssemblyBegin(A,MAT_FINAL_ASSEMBLY);
  MatAssemblyEnd(A,MAT_FINAL_ASSEMBLY);
  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                Create the linear solver and set various options
     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  /*
     Create linear solver context
  */
  KSPCreate(PETSC_COMM_WORLD,&ksp);

  
     /*Set operators. Here the matrix that defines the linear system
     also serves as the preconditioning matrix.
  */
  KSPSetOperators(ksp,A,A);

  /*
     Set linear solver defaults for  problem (optional).
     - By extracting the KSP and PC contexts from the KSP context,
       we can then directly call any KSP and PC routines to set
       various options.
     - The following four statements are optional; all of these
       parameters could alternatively be specified at runtime via
       KSPSetFromOptions();
  */
  KSPSetTolerances(ksp,1.e-10,PETSC_DEFAULT,PETSC_DEFAULT,PETSC_DEFAULT);

  /*
    Set runtime options, e.g.,
        -ksp_type <type> -pc_type <type> -ksp_monitor -ksp_rtol <rtol>
    These options will override those specified above as long as
    KSPSetFromOptions() is called _after_ any other customization
    routines.
  */
  KSPSetFromOptions(ksp);//CHKERRQ(ierr);

 
    PetscScalar p = .5;
    VecSet(x,p);
    KSPSetInitialGuessNonzero(ksp,PETSC_TRUE);

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                      Solve the linear system
     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  /*
     Solve linear system
  */
  KSPSolve(ksp,b,x);


  /*
     View solver info; we could instead use the option -ksp_view to
     print  info to the screen at the conclusion of KSPSolve().
  */

  PetscInt ix[1];
  for(int i=0;i<n;i++)
  {
    ix[0] = i;
    VecGetValues(x,1,ix,Valor);
    this->CampodeTemperaturas[i] = Valor[0];
  }

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
                      Check solution and clean up
     - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  /*
     Check the error
  */
  VecNorm(x,NORM_2,&norm);
  KSPGetIterationNumber(ksp,&its);

  /*
     Free work space.  All PETSc objects should be destroyed when they
     are no longer needed.
  */
  VecDestroy(&x);
  VecDestroy(&b);
  MatDestroy(&A);
  KSPDestroy(&ksp);

  /*
     Always call PetscFinalize() before exiting a program.   routine
       - finalizes the PETSc libraries as well as MPI
       - provides summary and diagnostic information if certain runtime
         options are chosen (e.g., -log_view).
  */
  
  return(this->CampodeTemperaturas);
}
vector<double> SolverLinear::getCampodeTemperaturasTDMA()
{
  double NaN;
  double DEN;
  NaN = nan("");

  vector<double> A;
  vector<double> B;
  vector<double> C;
  vector<double> D;

  A.resize(this->nint);
  B.resize(this->nint);
  C.resize(this->nint);
  D.resize(this->nint);

  A[0] = this->Avec[0][0];
  B[0] = this->Avec[0][1];
  C[0] = NaN;
  D[0] = this->bvec[0];
  for(int i=1; i<this->nint-1; i++)
  {
    A[i] = this->Avec[i][i];
    B[i] = this->Avec[i][i+1];
    C[i] = this->Avec[i][i-1];
    D[i] = this->bvec[i];
  }
  A[this->nint-1]=this->Avec[this->nint-1][this->nint-1];
  B[this->nint-1]=NaN;
  C[this->nint-1]=this->Avec[this->nint-1][this->nint-2];
  D[this->nint-1]=this->bvec[this->nint-1];


  for(int i=1; i<nint; i++)
  {
    DEN=C[i]/A[i-1];
    A[i]=A[i]-DEN*B[i-1];
    D[i]=D[i]-DEN*D[i-1];
  }
  this->CampodeTemperaturas[nint-1]=D[nint-1]/A[nint-1];
  for(int i=nint-2; i>-1; i--)
  {
    this->CampodeTemperaturas[i]=(D[i]-B[i]*this->CampodeTemperaturas[i+1])/A[i];
  }
  return(this->CampodeTemperaturas);
}