/*
 * Copyright 2020 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdint.h>
#include <cmath>

#define MAXN 2048

void cpu_cholesky(int diagSize, double *matrixA) {

   double dataA[diagSize][diagSize];

   for(int i = 0; i < diagSize; i++){
      for (int j = 0; j < diagSize; j++) {
         dataA[i][j] = matrixA[i*diagSize + j];
      }
   }

   double tmp1=sqrt(dataA[0][0]);

   dataA[0][0] = tmp1;
   Loop_first_col:
   for (int i = 1; i < diagSize; i++){
      dataA[i][0] = dataA[i][0]/tmp1;
   }

   Loop_col:
   for (int j = 1; j < diagSize; ++j){
      double tmp = 0;

      Loop_diag:
      for(int k = 0; k < j; k++){
         tmp += dataA[j][k]*dataA[j][k];
      }
      dataA[j][j] = sqrt(dataA[j][j] - tmp);
      if (j < diagSize - 1){
         Loop_row:
         for(int i = j+1; i < diagSize; ++i){
            double tmp2=0;
            Loop_vec_mul:
            for(int k = 0; k < j; k++){
              tmp2 += dataA[i][k]*dataA[j][k];
            }
            dataA[i][j] = (dataA[i][j] - tmp2)/dataA[j][j];
         }
      }
   }

   for (int i = 0; i < diagSize; i++) {
      for (int j = 0; j < diagSize; j++) {
         matrixA[i * diagSize + j] = dataA[i][j];
      }
   }
}
