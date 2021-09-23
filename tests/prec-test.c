// Precedence testing for expressions.

// reduce before shift

int r001(int a, int b, int c) { return a * b*c; }
int r002(int a, int b, int c) { if (c == 0)  return 1; else return a * b / c; }
int r003(int a, int b, int c) { return a * b + c; }
int r004(int a, int b, int c) { return a * b - c; }
int r005(int a, int b, int c) { return a * b < c; }
int r006(int a, int b, int c) { return a * b > c; }
int r007(int a, int b, int c) { return a * b <= c; }
int r008(int a, int b, int c) { return a * b >= c; }
int r009(int a, int b, int c) { return a * b == c; }
int r010(int a, int b, int c) { return a * b != c; }
int r011(int a, int b, int c) { return a * b&&c; }
int r012(int a, int b, int c) { return a * b || c; }

int r013(int a, int b, int c) { return a / b * c; }
int r014(int a, int b, int c) { if ((c == 0) || (b == 0)) return 1; else return a / b / c; }
int r015(int a, int b, int c) { if (b == 0) return 1; else return a / b + c; }
int r016(int a, int b, int c) { if (b == 0) return 1; else return a / b - c; }
int r017(int a, int b, int c) { if (b == 0) return 1; else return a / b < c; }
int r018(int a, int b, int c) { if (b == 0) return 1; else return a / b > c; }
int r019(int a, int b, int c) { if (b == 0) return 1; else return a / b <= c; }
int r020(int a, int b, int c) { if (b == 0) return 1; else return a / b >= c; }
int r021(int a, int b, int c) { if (b == 0) return 1; else return a / b == c; }
int r022(int a, int b, int c) { if (b == 0) return 1; else return a / b != c; }
int r023(int a, int b, int c) { if (b == 0) return 1; else return a / b && c; }
int r024(int a, int b, int c) { if (b == 0) return 1; else return a / b || c; }

int r025(int a, int b, int c) { return a + b + c; }
int r026(int a, int b, int c) { return a + b - c; }
int r027(int a, int b, int c) { return a + b < c; }
int r028(int a, int b, int c) { return a + b > c; }
int r029(int a, int b, int c) { return a + b <= c; }
int r030(int a, int b, int c) { return a + b >= c; }
int r031(int a, int b, int c) { return a + b == c; }
int r032(int a, int b, int c) { return a + b != c; }
int r033(int a, int b, int c) { return a + b && c; }
int r034(int a, int b, int c) { return a + b || c; }

int r035(int a, int b, int c) { return a - b + c; }
int r036(int a, int b, int c) { return a - b - c; }
int r037(int a, int b, int c) { return a - b < c; }
int r038(int a, int b, int c) { return a - b > c; }
int r039(int a, int b, int c) { return a - b <= c; }
int r040(int a, int b, int c) { return a - b >= c; }
int r041(int a, int b, int c) { return a - b == c; }
int r042(int a, int b, int c) { return a - b != c; }
int r043(int a, int b, int c) { return a - b && c; }
int r044(int a, int b, int c) { return a - b || c; }

int r045(int a, int b, int c) { return a < b < c; }
int r046(int a, int b, int c) { return a<b>c; }
int r047(int a, int b, int c) { return a < b <= c; }
int r048(int a, int b, int c) { return a < b >= c; }
int r049(int a, int b, int c) { return a < b == c; }
int r050(int a, int b, int c) { return a < b != c; }
int r051(int a, int b, int c) { return a < b&&c; }
int r052(int a, int b, int c) { return a < b || c; }

int r053(int a, int b, int c) { return a > b < c; }
int r054(int a, int b, int c) { return a > b > c; }
int r055(int a, int b, int c) { return a > b <= c; }
int r056(int a, int b, int c) { return a > b >= c; }
int r057(int a, int b, int c) { return a > b == c; }
int r058(int a, int b, int c) { return a > b != c; }
int r059(int a, int b, int c) { return a > b&&c; }
int r060(int a, int b, int c) { return a > b || c; }

int r061(int a, int b, int c) { return a <= b < c; }
int r062(int a, int b, int c) { return a <= b > c; }
int r063(int a, int b, int c) { return a <= b <= c; }
int r064(int a, int b, int c) { return a <= b >= c; }
int r065(int a, int b, int c) { return a <= b == c; }
int r066(int a, int b, int c) { return a <= b != c; }
int r067(int a, int b, int c) { return a <= b && c; }
int r068(int a, int b, int c) { return a <= b || c; }

int r069(int a, int b, int c) { return a >= b < c; }
int r070(int a, int b, int c) { return a >= b > c; }
int r071(int a, int b, int c) { return a >= b <= c; }
int r072(int a, int b, int c) { return a >= b >= c; }
int r073(int a, int b, int c) { return a >= b == c; }
int r074(int a, int b, int c) { return a >= b != c; }
int r075(int a, int b, int c) { return a >= b && c; }
int r076(int a, int b, int c) { return a >= b || c; }

int r077(int a, int b, int c) { return a == b == c; }
int r078(int a, int b, int c) { return a == b != c; }
int r079(int a, int b, int c) { return a == b && c; }
int r080(int a, int b, int c) { return a == b || c; }

int r081(int a, int b, int c) { return a != b == c; }
int r082(int a, int b, int c) { return a != b != c; }
int r083(int a, int b, int c) { return a != b && c; }
int r084(int a, int b, int c) { return a != b || c; }

int r085(int a, int b, int c) { return a && b&&c; }
int r086(int a, int b, int c) { return a && b || c; }

int r087(int a, int b, int c) { return a || b || c; }

// Unary
int r088(int a, int b, int c) { return -b * c; }
int r089(int a, int b, int c) { if (c == 0) return 1; else return -b / c; }
int r090(int a, int b, int c) { return -b + c; }
int r091(int a, int b, int c) { return -b - c; }
int r092(int a, int b, int c) { return -b < c; }
int r093(int a, int b, int c) { return -b > c; }
int r094(int a, int b, int c) { return -b <= c; }
int r095(int a, int b, int c) { return -b >= c; }
int r096(int a, int b, int c) { return -b == c; }
int r097(int a, int b, int c) { return -b != c; }
int r098(int a, int b, int c) { return -b && c; }
int r099(int a, int b, int c) { return -b || c; }

int r100(int a, int b, int c) { return !b*c; }
int r101(int a, int b, int c) { if (c == 0) return 1; else return !b / c; }
int r102(int a, int b, int c) { return !b + c; }
int r103(int a, int b, int c) { return !b - c; }
int r104(int a, int b, int c) { return !b < c; }
int r105(int a, int b, int c) { return !b > c; }
int r106(int a, int b, int c) { return !b <= c; }
int r107(int a, int b, int c) { return !b >= c; }
int r108(int a, int b, int c) { return !b == c; }
int r109(int a, int b, int c) { return !b != c; }
int r110(int a, int b, int c) { return !b&&c; }
int r111(int a, int b, int c) { return !b || c; }


// Precedence testing for expressions.

//  Shift before reduce.

// Binary operators

int r112(int a, int b, int c) { return b + c * a; }
int r113(int a, int b, int c) { return b - c * a; }
int r114(int a, int b, int c) { return b < c*a; }
int r115(int a, int b, int c) { return b > c*a; }
int r116(int a, int b, int c) { return b <= c * a; }
int r117(int a, int b, int c) { return b >= c * a; }
int r118(int a, int b, int c) { return b == c * a; }
int r119(int a, int b, int c) { return b != c * a; }
int r120(int a, int b, int c) { return b && c*a; }
int r121(int a, int b, int c) { return b || c * a; }

int r122(int a, int b, int c) { return b + c / a; }
int r123(int a, int b, int c) { return b - c / a; }
int r124(int a, int b, int c) { return b < c / a; }
int r125(int a, int b, int c) { return b > c / a; }
int r126(int a, int b, int c) { return b <= c / a; }
int r127(int a, int b, int c) { return b >= c / a; }
int r128(int a, int b, int c) { return b == c / a; }
int r129(int a, int b, int c) { return b != c / a; }
int r130(int a, int b, int c) { return b && c / a; }
int r131(int a, int b, int c) { return b || c / a; }

int r132(int a, int b, int c) { return b < c + a; }
int r133(int a, int b, int c) { return b > c + a; }
int r134(int a, int b, int c) { return b <= c + a; }
int r135(int a, int b, int c) { return b >= c + a; }
int r136(int a, int b, int c) { return b == c + a; }
int r137(int a, int b, int c) { return b != c + a; }
int r138(int a, int b, int c) { return b && c + a; }
int r139(int a, int b, int c) { return b || c + a; }

int r140(int a, int b, int c) { return b < c - a; }
int r141(int a, int b, int c) { return b > c - a; }
int r142(int a, int b, int c) { return b <= c - a; }
int r143(int a, int b, int c) { return b >= c - a; }
int r144(int a, int b, int c) { return b == c - a; }
int r145(int a, int b, int c) { return b != c - a; }
int r146(int a, int b, int c) { return b && c - a; }
int r147(int a, int b, int c) { return b || c - a; }

int r148(int a, int b, int c) { return b == c < a; }
int r149(int a, int b, int c) { return b != c < a; }
int r150(int a, int b, int c) { return b && c < a; }
int r151(int a, int b, int c) { return b || c < a; }

int r152(int a, int b, int c) { return b == c > a; }
int r153(int a, int b, int c) { return b != c > a; }
int r154(int a, int b, int c) { return b && c > a; }
int r155(int a, int b, int c) { return b || c > a; }

int r156(int a, int b, int c) { return b == c >= a; }
int r157(int a, int b, int c) { return b != c >= a; }
int r158(int a, int b, int c) { return b && c >= a; }
int r159(int a, int b, int c) { return b || c >= a; }

int r160(int a, int b, int c) { return b == c <= a; }
int r161(int a, int b, int c) { return b != c <= a; }
int r162(int a, int b, int c) { return b && c <= a; }
int r163(int a, int b, int c) { return b || c <= a; }

int r164(int a, int b, int c) { return b && c == a; }
int r165(int a, int b, int c) { return b || c == a; }

int r166(int a, int b, int c) { return b && c != a; }
int r167(int a, int b, int c) { return b || c != a; }

int r168(int a, int b, int c) { return b || c && a; }

int r169(int a, int b, int c) { return b && c <= a; }
int r170(int a, int b, int c) { return b || c <= a; }
