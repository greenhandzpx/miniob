/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by wangyunlai on 2022/9/28
//

#include <string.h>
#include "util/util.h"

std::string double2string(double v)
{
  char buf[256];
  snprintf(buf, sizeof(buf), "%.2f", v);
  size_t len = strlen(buf);
  while (buf[len - 1] == '0') {
    len--;
      
  }
  if (buf[len - 1] == '.') {
    len--;
  }

  return std::string(buf, len);
}


// ***************************typecast*****************************************
bool is_num(char c) {
   return c - '0' >= 0 && c - '0' <= 9;
}

float convert2float(std::string str, int idx) {
   return (float)std::stoi(str.substr(0, idx));
}

float convert2float(std::string str, int beforedot, int afterdot) {
    int start1 = 0, len1 = beforedot;
    int start2 = beforedot + 1, len2 = afterdot - beforedot - 1;
    std::string s1 = str.substr(start1, len1);
    std::string s2 = str.substr(start2, len2);
    
   float num1 = std::stoi(s1);
   float num2 = std::stoi(s2);

   int k = 1;
   for (int i = 0; i < len2; i++) k *= 10;

   return num1 + num2 / (float)k;
}

/**
* convert string to float
* @param str string to convert
* @param[out] num num of string converted
* @return true if success, false otherwise

*/


bool string2float(std::string str, float* num) {

   int status = 0;
   int len = str.size();

   int beforedot = 0;

   for (int i = 0; i < len; i++) {
      switch (status) {
         case 0:
         if (is_num(str[i])) status = 1;
         else return false;
         break;

         case 1:
         if (is_num(str[i])) status = 1;
         else if (str[i] == '.') {
            beforedot = i;
            status = 2;
         }
         else {
            *num = convert2float(str, i);
            return true;
         }
         break;

         case 2:
         if (is_num(str[i])) status = 3;
         else {
            *num = convert2float(str, i - 1);
            return true;
         }
         break;

         case 3:
         if (is_num(str[i])) status = 3;
         else {
            *num = convert2float(str, beforedot, i);
            return true;
         }
         break;

         default:
         return false;
      }
   }

   // 4 case
   if (len == 0) return false;
   else if (str[len - 1] == '.') {
      *num = convert2float(str, len - 1);
      return true;
   } else if (beforedot == 0) {
      *num = convert2float(str, len);
      return true;
   } else {
      *num = convert2float(str, beforedot, len);
      return true;
   }
}

// ***************************typecast*****************************************