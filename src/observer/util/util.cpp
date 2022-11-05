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
#include <vector>
#include <sstream>

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


// ********************************like*****************************************

int KMP(std::string p, std::string s) {
   int n = s.size(), m = p.size();
   if(m == 0) return 0;  
   s.insert(s.begin(),' ');
   p.insert(p.begin(),' ');
   std::vector<int> next(m + 1);
   for(int i = 2, j = 0; i <= m; i++){
       while(j and p[i] != p[j + 1]) j = next[j];
       if(p[i] == p[j + 1]) j++;
       next[i] = j;
   }
   for(int i = 1, j = 0; i <= n; i++){
       while(j and (s[i] != p[j + 1] && p[j + 1] != '_')) j = next[j];
       if(s[i] == p[j + 1] || p[j + 1] == '_') j++;
       if(j == m) return i;
   }
   return -1;
}

bool is_like_pre(std::string s1, std::string s2) 
{
   // first we use '%' to split the s2 into substring array, called subs2
   std::stringstream stream_data(s2);
   std::vector<std::string> subs2;
   std::string res;

   while (std::getline(stream_data, res, '%')) {
      subs2.push_back(res);
   }

   std::vector<std::string>::iterator it = subs2.begin();
   while (it != subs2.end()) {
      if (*it == "") it = subs2.erase(it);
      else it++;
   }


   // then, we get the first substring matching subs2[0] in s1 by KMP algorithm, and end1 is the last index of substring in s1, '_' can match every char
   // we use end1(start) to cut and get the new s1, repeat above process to get substring and cut util all of the string in sub2 is matching
   // if one is not matching, we return false

   // notice: here '_' always match the char with least index, in this situcation, abcd like %_, it will be false, but in fact it is true

   int endn[subs2.size()];
   int start = 0;

   for (int i = 0; i < subs2.size(); i++) {
      std::string s3 = s1.substr(start);
      int res = KMP(subs2[i], s3); 
      if (res == -1) return false;
      start += res;
      endn[i] = start;
   }

   // if the start index of subs2[0] in s1 do not equal to 0 and the first char in s2 is not '%',
   // or the end index of subs2[subs2.length - 1]  in s1 do not equal to s1.length and the last char in s1 is not '%', return false
  
   if (endn[0] - subs2[0].size() != 0 && s2[0] != '%') return false;
   if (endn[subs2.size() - 1] != (int)s1.size() && s2[s2.size() - 1] != '%') return false;
 
   // return true
   return true;
}

bool is_like_bhd(std::string s1, std::string s2) {
   std::string s3(s1);
   std::string s4(s2);

   int i, j;

   int len1 = s3.size();
   i = 0;
   j = len1 - 1;

   while (i < j) {
      char c = s3[i];
      s3[i] = s3[j];
      s3[j] = c;
      i++;
      j--;
   }

   int len2 = s4.size();
   i = 0;
   j = len2 - 1;

   while (i < j) {
      char c = s4[i];
      s4[i] = s4[j];
      s4[j] = c;
      i++;
      j--;
   }
   
   return is_like_pre(s3, s4);
}



bool is_like(std::string s1, std::string s2) 
{
   if (s1.size() == 0 && s2.size() == 0) return true;
   if (s1.size() != 0 && s2.size() == 0) return false;

   int cnt_ = 0;
   for (int i = 0; i < s2.size(); i++)
      if (s2[i] == '_') cnt_++;

   int cnto = 0;
   for (int i = 0; i < s2.size(); i++)
      if (s2[i] == '%') cnto ++;

   // if all chars in s2 is '_' or '%'
   if (cnt_ + cnto == s2.size()) {
      if (cnto == s2.size()) return true;
      else if (cnt_ == s2.size()) {
         if (cnt_ == s1.size()) return true;
         else return false;
      } else {
         if (cnt_ > s1.size()) return false;
         else return true;
      }
   }
   


   return is_like_pre(s1, s2) || is_like_bhd(s1, s2);
}
// ********************************like*****************************************


// ********************************func*****************************************


float round(float f, int num)
{
   int d = 1;
   for (; num != 0; num--) d *= 10;
   int i = f * d;
   float ii = f * d;
   if (ii - i >= 0.5) i += 1;
   f = (float)i;
   return f / d;
}

float round1(float f)
{
   float ff = (float)((int)f);
   if (f - ff >= 0.5) {
      return ff + 1;
   } else {
      return ff;
   }
}

char* date_format(int date, char* format) 
{
   int year = date / 10000;
   int y = year - ((year / 100) * 100);
   int month = (date / 100) - (year * 100);
   int day = date - (year * 10000) - (month * 100);

   std::stringstream stream_data(format);
   std::vector<std::string> subs2;
   std::string res;

   while (std::getline(stream_data, res, '-')) {
      subs2.push_back(res);
   }

   std::vector<std::string>::iterator it = subs2.begin();
   while (it != subs2.end()) {
      if (*it == "") it = subs2.erase(it);
      else it++;
   }

   std::string s = std::string("");
   it = subs2.begin();
   while (it != subs2.end()) {
      
      if (*it == "%Y") {
         s.append(std::to_string(year));
         s.append("-");
         // std::cout << s  <<std::endl;
      } else if (*it == "%y") {
         if (y < 10) s.append("0");
         s.append(std::to_string(y));
         s.append("-");
         // std::cout << s  <<std::endl;
      } else if (*it == "%m") {
         if (month < 10) s.append("0");
         s.append(std::to_string(month));
         s.append("-");
         // std::cout << s  <<std::endl;
      } else if (*it == "%d") {
         if (day < 10) s.append("0");
         s.append(std::to_string(day));
         s.append("-");
         // std::cout << s  <<std::endl;
      } else {
         s = "invalid";
      }
      it++;
   }
   return const_cast<char*>(s.substr(0, s.size() - 1).data());
}
// ********************************func*****************************************
