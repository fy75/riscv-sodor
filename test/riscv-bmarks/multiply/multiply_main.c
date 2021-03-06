// *************************************************************************
// multiply filter bencmark
// -------------------------------------------------------------------------
//
// This benchmark tests the software multiply implemenation. The
// input data (and reference data) should be generated using the
// multiply_gendata.pl perl script and dumped to a file named
// dataset1.h You should not change anything except the
// HOST_DEBUG and VERIFY macros for your timing run.

#include "multiply.h"
#include "util.h"

//--------------------------------------------------------------------------
// Macros

// Set VERIFY to 1 if you want the program to check that the sort
// function returns the right answer. When you are doing your 
// benchmarking you should set this to 0 so that the verification
// is not included in your timing.

#ifndef VERIFY
#define VERIFY     1
#endif

//--------------------------------------------------------------------------
// Input/Reference Data

#include "dataset1.h"

//--------------------------------------------------------------------------
// Helper functions

int verify( int n, int test[], int correct[] )
{
  int i;
  for ( i = 0; i < n; i++ ) {
    if ( test[i] != correct[i] ) {
      return 2;
    }
  }
  return 1;
}

#if HOST_DEBUG
void printArray( char name[], int n, int arr[] )
{
  int i;
  printf( " %10s :", name );
  for ( i = 0; i < n; i++ )
    printf( " %3d ", arr[i] );
  printf( "\n" );
}
#endif

//--------------------------------------------------------------------------
// Main

int main( int argc, char* argv[] )
{
  int i;
  int results_data[DATA_SIZE];

  // Output the input arrays

#if HOST_DEBUG
  printArray( "input1",  DATA_SIZE, input_data1  );
  printArray( "input2",  DATA_SIZE, input_data2  );
  printArray( "verify", DATA_SIZE, verify_data );
#endif

#if ( !HOST_DEBUG && PREALLOCATE )
  for (i = 0; i < DATA_SIZE; i++)
  {
    results_data[i] = multiply( input_data1[i], input_data2[i] );
  }
#endif

#if HOST_DEBUG
  for (i = 0; i < DATA_SIZE; i++)
  {
    results_data[i] = multiply( input_data1[i], input_data2[i] );
  }
#else
  setStats(1);
  for (i = 0; i < DATA_SIZE; i++)
  {
    results_data[i] = multiply( input_data1[i], input_data2[i] );
  }
  setStats(0);
#endif
  
  // Print out the results

#if HOST_DEBUG
  printArray( "results", DATA_SIZE, results_data );
#endif

  // Check the results

  finishTest(verify( DATA_SIZE, results_data, verify_data ));

}
