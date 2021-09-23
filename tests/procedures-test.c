int a,b,c;

int func(int param1, int param2, int param3)
{ int local1,local2,local3;

  a = 11;
  b = 7;
  c = 3;
  a = b + c;
  c = b - a;
  b = a * c;
  a = b / c;
  
  local1 = param1 + param2;
  local2 = param1 - param2;
  local3 = param1 * param2;
  param1 = local1 / local2 + local3;

}

  
