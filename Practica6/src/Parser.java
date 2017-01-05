//### This file created by BYACC 1.8(/Java extension  1.15)
//### Java capabilities added 7 Jan 97, Bob Jamison
//### Updated : 27 Nov 97  -- Bob Jamison, Joe Nieten
//###           01 Jan 98  -- Bob Jamison -- fixed generic semantic constructor
//###           01 Jun 99  -- Bob Jamison -- added Runnable support
//###           06 Aug 00  -- Bob Jamison -- made state variables class-global
//###           03 Jan 01  -- Bob Jamison -- improved flags, tracing
//###           16 May 01  -- Bob Jamison -- added custom stack sizing
//###           04 Mar 02  -- Yuval Oren  -- improved java performance, added options
//###           14 Mar 02  -- Tomas Hurka -- -d support, static initializer workaround
//### Please send bug reports to tom@hukatronic.cz
//### static char yysccsid[] = "@(#)yaccpar	1.8 (Berkeley) 01/20/90";






//#line 4 "P6.y"
	import java.lang.Math;
	import java.io.*;
	import java.util.StringTokenizer;
//#line 21 "Parser.java"




public class Parser
{

boolean yydebug;        //do I want debug output?
int yynerrs;            //number of errors so far
int yyerrflag;          //was there an error?
int yychar;             //the current working character

//########## MESSAGES ##########
//###############################################################
// method: debug
//###############################################################
void debug(String msg)
{
  if (yydebug)
    System.out.println(msg);
}

//########## STATE STACK ##########
final static int YYSTACKSIZE = 500;  //maximum stack size
int statestk[] = new int[YYSTACKSIZE]; //state stack
int stateptr;
int stateptrmax;                     //highest index of stackptr
int statemax;                        //state when highest index reached
//###############################################################
// methods: state stack push,pop,drop,peek
//###############################################################
final void state_push(int state)
{
  try {
		stateptr++;
		statestk[stateptr]=state;
	 }
	 catch (ArrayIndexOutOfBoundsException e) {
     int oldsize = statestk.length;
     int newsize = oldsize * 2;
     int[] newstack = new int[newsize];
     System.arraycopy(statestk,0,newstack,0,oldsize);
     statestk = newstack;
     statestk[stateptr]=state;
  }
}
final int state_pop()
{
  return statestk[stateptr--];
}
final void state_drop(int cnt)
{
  stateptr -= cnt; 
}
final int state_peek(int relative)
{
  return statestk[stateptr-relative];
}
//###############################################################
// method: init_stacks : allocate and prepare stacks
//###############################################################
final boolean init_stacks()
{
  stateptr = -1;
  val_init();
  return true;
}
//###############################################################
// method: dump_stacks : show n levels of the stacks
//###############################################################
void dump_stacks(int count)
{
int i;
  System.out.println("=index==state====value=     s:"+stateptr+"  v:"+valptr);
  for (i=0;i<count;i++)
    System.out.println(" "+i+"    "+statestk[i]+"      "+valstk[i]);
  System.out.println("======================");
}


//########## SEMANTIC VALUES ##########
//public class ParserVal is defined in ParserVal.java


String   yytext;//user variable to return contextual strings
ParserVal yyval; //used to return semantic vals from action routines
ParserVal yylval;//the 'lval' (result) I got from yylex()
ParserVal valstk[];
int valptr;
//###############################################################
// methods: value stack push,pop,drop,peek.
//###############################################################
void val_init()
{
  valstk=new ParserVal[YYSTACKSIZE];
  yyval=new ParserVal();
  yylval=new ParserVal();
  valptr=-1;
}
void val_push(ParserVal val)
{
  if (valptr>=YYSTACKSIZE)
    return;
  valstk[++valptr]=val;
}
ParserVal val_pop()
{
  if (valptr<0)
    return new ParserVal();
  return valstk[valptr--];
}
void val_drop(int cnt)
{
int ptr;
  ptr=valptr-cnt;
  if (ptr<0)
    return;
  valptr = ptr;
}
ParserVal val_peek(int relative)
{
int ptr;
  ptr=valptr-relative;
  if (ptr<0)
    return new ParserVal();
  return valstk[ptr];
}
final ParserVal dup_yyval(ParserVal val)
{
  ParserVal dup = new ParserVal();
  dup.ival = val.ival;
  dup.dval = val.dval;
  dup.sval = val.sval;
  dup.obj = val.obj;
  return dup;
}
//#### end semantic value section ####
public final static short IF=257;
public final static short ELSE=258;
public final static short WHILE=259;
public final static short FOR=260;
public final static short COMP=261;
public final static short DIFERENTES=262;
public final static short MAY=263;
public final static short MEN=264;
public final static short MAYI=265;
public final static short MENI=266;
public final static short FNCT=267;
public final static short NUMBER=268;
public final static short VAR=269;
public final static short AND=270;
public final static short OR=271;
public final static short FUNC=272;
public final static short RETURN=273;
public final static short PARAMETRO=274;
public final static short PROC=275;
public final static short YYERRCODE=256;
final static short yylhs[] = {                           -1,
    0,    0,    0,    1,    1,    1,    1,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    2,    2,    2,    2,    2,    2,    2,    2,    7,    7,
    7,    8,    3,    3,    3,    3,    3,    3,   16,   14,
    6,   15,   10,    9,   11,   12,   13,   13,   13,    4,
    5,    5,   17,   17,
};
final static short yylen[] = {                            2,
    0,    2,    3,    2,    1,    3,    2,    1,    1,    8,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    2,    4,    2,    1,    4,    0,    1,
    3,    0,   14,   11,   10,   16,    8,    8,    1,    1,
    1,    0,    0,    1,    1,    1,    0,    1,    3,    1,
    1,    3,    1,    3,
};
final static short yydefred[] = {                         1,
    0,   44,   45,   46,    0,    9,    0,   40,    0,   27,
   39,    0,    2,    0,    0,    0,    5,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   26,    0,    0,    3,
    0,    7,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    4,    0,    0,    0,    0,   41,    0,
    0,    0,    0,   50,    0,   15,    6,    0,    0,    0,
    0,    0,    0,    0,   23,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   25,    0,   28,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   53,    0,    0,    0,    0,    0,    0,    0,   10,    0,
    0,    0,    0,    0,   37,   38,    0,   54,    0,   43,
    0,    0,   43,   35,    0,    0,   34,    0,    0,    0,
    0,    0,   33,    0,   43,   36,
};
final static short yydgoto[] = {                          1,
   15,   16,   17,   55,  102,   18,   70,  123,   19,   81,
   20,   21,   74,   22,  107,   23,  103,
};
final static short yysindex[] = {                         0,
    9,    0,    0,    0,  -24,    0,  -52,    0,  -13,    0,
    0,  -13,    0,  -13,   28,   86,    0,  -11,   -3,    1,
    5, -238, -238,  -13,  -13, -212,    0, -146,   54,    0,
   97,    0,  -13,  -13,  -13,  -13,  -13,  -13,  -13,  -13,
  -13,  -13,  -13,    0,  -13,  -13,  -13,  -13,    0,   52,
   63,   65,  108,    0,  -35,    0,    0,  -53,  150, -107,
 -166,  -78, -146, -201,    0,  119,  119,  -63,  108,  -26,
  108,  108,  108,   34,   73,   81,    0,   69,    0,  -13,
  105,  111,  -13,   90,   47,   53,   61,  108,   64,   67,
  108,  -13,  -32,  -32,  -72,  -32,  -32,  108,  -32,  -32,
    0,   19,  160,  -32,  -32,  146,   89,   91,    0,  -72,
  -62,   94,   95,  -13,    0,    0,  160,    0,  -43,    0,
   34,   98,    0,    0,  181,  -32,    0,  103,  -32,  -32,
  104,  -32,    0,  113,    0,    0,
};
final static short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,   43,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  130,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   16,    0,    0,  -42,    0,    0,
    0,    0,   18,    0,    0,    0,    0,   -9,  -38,   30,
  -31,   10,  136,   76,    0,  -19,   68,   22,   38,    0,
  198,  198,   57,  185,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   49,    0,    0,
   82,    0,    0,    0,    0,    0,    0,  185,  120,  120,
    0,    0,   23,  121,  121,    0,    0,    0,    0,    0,
    0,    0,    0,   50,    0,    0,   44,    0,  -10,    0,
  198,    0,    0,    0,    0,    0,    0,    0,  121,    0,
    0,  121,    0,    0,    0,    0,
};
final static short yygindex[] = {                         0,
  -50,  394,   33,    0,    0,  132,    0,    0,    0,   62,
    0,    0,  134,    0,  151,    0,  143,
};
final static int YYTABLESIZE=526;
static short yytable[];
static { yytable();}
static void yytable(){
yytable = new short[]{                         32,
   12,   47,   17,   17,   17,   17,   17,   14,   25,   18,
   18,   18,   18,   18,   79,   24,   47,   80,   13,   12,
   17,   13,   32,   13,   13,   13,   14,   18,   45,   32,
   49,   16,   16,   16,   16,   16,   46,   30,   26,   13,
   47,   12,   99,  100,   48,  104,  105,   32,   14,   16,
   21,   21,   21,   21,   21,   54,   29,   78,   11,   29,
   12,   11,   12,   12,   12,   12,   12,   14,   21,   40,
   20,   20,   20,   20,   20,  129,   11,   83,   30,  132,
   12,   30,   41,    8,    8,    8,    8,    8,   20,   31,
   47,   75,   31,   47,   56,   43,   41,   48,   42,   38,
   48,    8,   76,   39,   40,   77,   43,   41,   14,   42,
   14,   14,   14,   85,   32,   48,   22,   22,   22,   22,
   22,   86,   49,   39,   40,   49,   14,   43,   41,   87,
   42,   32,   32,   82,   22,   84,   32,   32,   43,   41,
   49,   42,  110,  109,   44,   89,   51,   51,   92,   43,
   41,   90,   42,   50,   51,   57,   36,   37,   38,  106,
   43,   32,   39,   40,   32,  112,  113,   52,   52,   93,
   24,   24,   24,   24,   24,   94,   19,   19,   19,   19,
   19,  124,  125,   95,  127,   36,   96,   38,   24,   97,
  131,   39,   40,  134,   19,  101,  136,   33,   34,   35,
   36,   37,   38,  111,  114,  118,   39,   40,   34,   35,
   36,   37,   38,  115,  122,  116,   39,   40,  119,  120,
  126,  128,   17,   17,    2,  130,    3,    4,  133,   18,
   18,   18,   18,   18,    5,    6,    7,  135,   43,    8,
    9,   10,   11,   43,   42,   43,   32,  121,   32,   32,
  108,   16,  117,    5,    6,    7,   32,   32,   32,    9,
   10,   32,   32,   32,   32,    2,    0,    3,    4,    0,
   21,   21,   21,    0,   21,    5,    6,    7,    0,    0,
    8,    9,   10,   11,    2,    0,    3,    4,    0,    0,
   20,   20,   20,    0,    5,    6,    7,    0,    0,    8,
    9,   10,   11,    8,    8,    8,    8,    8,    8,    0,
    0,    0,    8,    8,   33,   34,   35,   36,   37,   38,
    0,    0,    0,   39,   40,   33,   34,   35,   36,   37,
   38,    0,    0,    0,   39,   40,   22,   22,   22,   22,
   22,   22,    0,    0,    0,   22,   33,   34,   35,   36,
   37,   38,    0,    0,    0,   39,   40,   33,   34,   35,
   36,   37,   38,    0,    0,    0,   39,   40,   33,   34,
   35,   36,   37,   38,    0,    0,    0,   39,   40,   33,
   34,   35,   36,   37,   38,    0,    0,    0,   39,   40,
   24,   24,   24,   24,   24,   24,   19,   19,   19,   19,
   19,   19,   27,    0,    0,   28,    0,   29,   31,    0,
    0,    0,   35,   36,   37,   38,    0,   52,   53,   39,
   40,    0,    0,    0,    0,    0,   58,   59,   60,   61,
   62,   63,   64,   65,   66,   67,   68,    0,   69,   71,
   72,   73,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   88,    0,    0,   91,    0,    0,    0,
    0,    0,    0,    0,    0,   98,    0,    0,    0,    0,
    0,    0,   31,   31,    0,    0,    0,   31,   31,    0,
    0,    0,    0,    0,    0,    0,    0,   73,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   31,    0,    0,   31,
};
}
static short yycheck[];
static { yycheck(); }
static void yycheck() {
yycheck = new short[] {                         10,
   33,   44,   41,   42,   43,   44,   45,   40,   61,   41,
   42,   43,   44,   45,   41,   40,   59,   44,   10,   33,
   59,   41,   33,   43,   44,   45,   40,   59,   40,   40,
  269,   41,   42,   43,   44,   45,   40,   10,   91,   59,
   40,   33,   93,   94,   40,   96,   97,   15,   40,   59,
   41,   42,   43,   44,   45,  268,   41,   93,   41,   44,
   33,   44,   41,   42,   43,   44,   45,   40,   59,  271,
   41,   42,   43,   44,   45,  126,   59,   44,   41,  130,
   59,   44,   40,   41,   42,   43,   44,   45,   59,   41,
   41,   40,   44,   44,   41,   42,   43,   41,   45,  266,
   44,   59,   40,  270,  271,   41,   42,   43,   41,   45,
   43,   44,   45,   41,  125,   59,   41,   42,   43,   44,
   45,   41,   41,  270,  271,   44,   59,   42,   43,   61,
   45,   99,  100,   72,   59,   74,  104,  105,   42,   43,
   59,   45,  124,  125,   59,   41,  124,  125,   59,   42,
   43,   41,   45,   22,   23,   59,  264,  265,  266,   98,
   42,  129,  270,  271,  132,  104,  105,  124,  125,  123,
   41,   42,   43,   44,   45,  123,   41,   42,   43,   44,
   45,  120,  121,  123,  123,  264,  123,  266,   59,  123,
  129,  270,  271,  132,   59,  268,  135,  261,  262,  263,
  264,  265,  266,   44,   59,  268,  270,  271,  262,  263,
  264,  265,  266,  125,  258,  125,  270,  271,  125,  125,
  123,   41,  261,  262,  257,  123,  259,  260,  125,  261,
  262,  263,  264,  265,  267,  268,  269,  125,   41,  272,
  273,  274,  275,   59,  125,  125,  257,  114,  259,  260,
  100,  261,  110,  267,  268,  269,  267,  268,  269,  273,
  274,  272,  273,  274,  275,  257,   -1,  259,  260,   -1,
  261,  262,  263,   -1,  265,  267,  268,  269,   -1,   -1,
  272,  273,  274,  275,  257,   -1,  259,  260,   -1,   -1,
  261,  262,  263,   -1,  267,  268,  269,   -1,   -1,  272,
  273,  274,  275,  261,  262,  263,  264,  265,  266,   -1,
   -1,   -1,  270,  271,  261,  262,  263,  264,  265,  266,
   -1,   -1,   -1,  270,  271,  261,  262,  263,  264,  265,
  266,   -1,   -1,   -1,  270,  271,  261,  262,  263,  264,
  265,  266,   -1,   -1,   -1,  270,  261,  262,  263,  264,
  265,  266,   -1,   -1,   -1,  270,  271,  261,  262,  263,
  264,  265,  266,   -1,   -1,   -1,  270,  271,  261,  262,
  263,  264,  265,  266,   -1,   -1,   -1,  270,  271,  261,
  262,  263,  264,  265,  266,   -1,   -1,   -1,  270,  271,
  261,  262,  263,  264,  265,  266,  261,  262,  263,  264,
  265,  266,    9,   -1,   -1,   12,   -1,   14,   15,   -1,
   -1,   -1,  263,  264,  265,  266,   -1,   24,   25,  270,
  271,   -1,   -1,   -1,   -1,   -1,   33,   34,   35,   36,
   37,   38,   39,   40,   41,   42,   43,   -1,   45,   46,
   47,   48,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   80,   -1,   -1,   83,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   92,   -1,   -1,   -1,   -1,
   -1,   -1,   99,  100,   -1,   -1,   -1,  104,  105,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  114,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  129,   -1,   -1,  132,
};
}
final static short YYFINAL=1;
final static short YYMAXTOKEN=275;
final static String yyname[] = {
"end-of-file",null,null,null,null,null,null,null,null,null,"'\\n'",null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,"'!'",null,null,null,null,null,null,"'('","')'","'*'","'+'",
"','","'-'",null,null,null,null,null,null,null,null,null,null,null,null,null,
"';'",null,"'='",null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,"'['",null,"']'",null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,"'{'","'|'","'}'",null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,null,
null,null,null,null,null,null,null,null,null,"IF","ELSE","WHILE","FOR","COMP",
"DIFERENTES","MAY","MEN","MAYI","MENI","FNCT","NUMBER","VAR","AND","OR","FUNC",
"RETURN","PARAMETRO","PROC",
};
final static String yyrule[] = {
"$accept : list",
"list :",
"list : list '\\n'",
"list : list linea '\\n'",
"linea : exp ';'",
"linea : stmt",
"linea : linea exp ';'",
"linea : linea stmt",
"exp : VAR",
"exp : NUMBER",
"exp : VAR '[' initNum ']' '=' '{' listaDeListas '}'",
"exp : VAR '=' exp",
"exp : exp '*' exp",
"exp : exp '+' exp",
"exp : exp '-' exp",
"exp : '(' exp ')'",
"exp : exp COMP exp",
"exp : exp DIFERENTES exp",
"exp : exp MEN exp",
"exp : exp MENI exp",
"exp : exp MAY exp",
"exp : exp MAYI exp",
"exp : exp AND exp",
"exp : exp OR exp",
"exp : '!' exp",
"exp : FNCT '(' exp ')'",
"exp : RETURN exp",
"exp : PARAMETRO",
"exp : nombreProc '(' arglist ')'",
"arglist :",
"arglist : exp",
"arglist : arglist ',' exp",
"nop :",
"stmt : if_ '(' exp stop_ ')' '{' linea stop_ '}' ELSE '{' linea stop_ '}'",
"stmt : if_ '(' exp stop_ ')' '{' linea stop_ '}' nop stop_",
"stmt : while_ '(' exp stop_ ')' '{' linea stop_ '}' stop_",
"stmt : for_ '(' instrucciones stop_ ';' exp stop_ ';' instrucciones stop_ ')' '{' linea stop_ '}' stop_",
"stmt : funcion nombreProc '(' ')' '{' linea null_ '}'",
"stmt : procedimiento nombreProc '(' ')' '{' linea null_ '}'",
"procedimiento : PROC",
"funcion : FUNC",
"nombreProc : VAR",
"null_ :",
"stop_ :",
"if_ : IF",
"while_ : WHILE",
"for_ : FOR",
"instrucciones :",
"instrucciones : exp",
"instrucciones : instrucciones ',' exp",
"initNum : NUMBER",
"listaDeListas : lista",
"listaDeListas : listaDeListas '|' lista",
"lista : NUMBER",
"lista : lista ',' NUMBER",
};

//#line 234 "P6.y"



TablaDeSimbolos tablaDeSimbolos = new TablaDeSimbolos();
MaquinaDePila maquina = new MaquinaDePila(tablaDeSimbolos);
int i = 0;
int j = 0;
double[][] auxiliar;
Matriz matrizAux = new Matriz();
Funcion funcionAux;
boolean huboError;

String ins;
StringTokenizer st;

void yyerror(String s){
	huboError = true;
	System.out.println("error:"+s);
}

boolean newline;
int yylex(){
	String s;
	int tok = 0;
	Double d;
	if (!st.hasMoreTokens()){
		if (!newline){
			newline=true;
			return '\n'; //So we look like classic YACC example
		}
		else
			return 0;
	}
	s = st.nextToken();
	try{
		d = Double.valueOf(s);/*this may fail*/
		yylval = new ParserVal(d.doubleValue()); //SEE BELOW
		return NUMBER;
	}
	catch (Exception e){}
	if(esVariable(s)){
		if(s.equals("proc")){
			return PROC;
		}
		if(s.charAt(0) == '$'){
			yylval = new ParserVal((int)Integer.parseInt(s.substring(1)));
			return PARAMETRO;
		}
		if(s.equals("return")){
			return RETURN;
		}
		if(s.equals("func")){
			return FUNC;
		}
		if(s.equals("==")){
			return COMP;
		}
		if(s.equals("!=")){
			return DIFERENTES;
		}
		if(s.equals("<")){
			return MEN;
		}
		if(s.equals("<=")){
			return MENI;
		}
		if(s.equals(">")){
			return MAY;
		}
		if(s.equals(">=")){
			return MAYI;
		}
		if(s.equals("&&")){
			return AND;
		}
		if(s.equals("||")){
			return OR;
		}
		if(s.equals("if")){
			return IF;
		}
		if(s.equals("else")){
			return ELSE;
		}
		if(s.equals("while")){
			return WHILE;
		}
		if(s.equals("for")){
			return FOR;
		}
		boolean esFuncion = false;
		Object objeto = tablaDeSimbolos.encontrar(s);
		if(objeto instanceof Funcion){
			funcionAux = (Funcion)objeto;
			yylval = new ParserVal(objeto);			
			esFuncion = true;
			return FNCT;
		}
		if(!esFuncion){
			yylval = new ParserVal(s);
			return VAR;
		}
	}
	else{
		tok = s.charAt(0);
	}
	//System.out.println("Token: " + tok);
	return tok;
}

String reservados[] = {"=", "{", "}", ",", "*", "+", "-", "(", ")", "|", "[", "]", ";", "!"};

boolean esVariable(String s){
	boolean cumple = true;
	for(int i = 0; i < reservados.length; i++)
		if(s.equals(reservados[i]))
			cumple = false;
	return cumple;
}

void dotest() throws Exception{
	tablaDeSimbolos.insertar("invert", new MaquinaDePila.invert());
	tablaDeSimbolos.insertar("print", new MaquinaDePila.print());
	tablaDeSimbolos.insertar("sum", new MaquinaDePila.sum());
	BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	while (true){
		huboError = false;
		try{
			ins = in.readLine();
		}
		catch (Exception e){}
		st = new StringTokenizer(ins);
		newline=false;
		//maquina = new MaquinaDePila(tablaDeSimbolos);
		yyparse();
		if(!huboError)
			maquina.ejecutar();
	}
}

public static void main(String args[]) throws Exception{
	Parser par = new Parser(false);
	par.dotest();
}
//#line 527 "Parser.java"
//###############################################################
// method: yylexdebug : check lexer state
//###############################################################
void yylexdebug(int state,int ch)
{
String s=null;
  if (ch < 0) ch=0;
  if (ch <= YYMAXTOKEN) //check index bounds
     s = yyname[ch];    //now get it
  if (s==null)
    s = "illegal-symbol";
  debug("state "+state+", reading "+ch+" ("+s+")");
}





//The following are now global, to aid in error reporting
int yyn;       //next next thing to do
int yym;       //
int yystate;   //current parsing state from state table
String yys;    //current token string


//###############################################################
// method: yyparse : parse input and execute indicated items
//###############################################################
int yyparse()
{
boolean doaction;
  init_stacks();
  yynerrs = 0;
  yyerrflag = 0;
  yychar = -1;          //impossible char forces a read
  yystate=0;            //initial state
  state_push(yystate);  //save it
  val_push(yylval);     //save empty value
  while (true) //until parsing is done, either correctly, or w/error
    {
    doaction=true;
    if (yydebug) debug("loop"); 
    //#### NEXT ACTION (from reduction table)
    for (yyn=yydefred[yystate];yyn==0;yyn=yydefred[yystate])
      {
      if (yydebug) debug("yyn:"+yyn+"  state:"+yystate+"  yychar:"+yychar);
      if (yychar < 0)      //we want a char?
        {
        yychar = yylex();  //get next token
        if (yydebug) debug(" next yychar:"+yychar);
        //#### ERROR CHECK ####
        if (yychar < 0)    //it it didn't work/error
          {
          yychar = 0;      //change it to default string (no -1!)
          if (yydebug)
            yylexdebug(yystate,yychar);
          }
        }//yychar<0
      yyn = yysindex[yystate];  //get amount to shift by (shift index)
      if ((yyn != 0) && (yyn += yychar) >= 0 &&
          yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
        {
        if (yydebug)
          debug("state "+yystate+", shifting to state "+yytable[yyn]);
        //#### NEXT STATE ####
        yystate = yytable[yyn];//we are in a new state
        state_push(yystate);   //save it
        val_push(yylval);      //push our lval as the input for next rule
        yychar = -1;           //since we have 'eaten' a token, say we need another
        if (yyerrflag > 0)     //have we recovered an error?
           --yyerrflag;        //give ourselves credit
        doaction=false;        //but don't process yet
        break;   //quit the yyn=0 loop
        }

    yyn = yyrindex[yystate];  //reduce
    if ((yyn !=0 ) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
      {   //we reduced!
      if (yydebug) debug("reduce");
      yyn = yytable[yyn];
      doaction=true; //get ready to execute
      break;         //drop down to actions
      }
    else //ERROR RECOVERY
      {
      if (yyerrflag==0)
        {
        yyerror("syntax error");
        yynerrs++;
        }
      if (yyerrflag < 3) //low error count?
        {
        yyerrflag = 3;
        while (true)   //do until break
          {
          if (stateptr<0)   //check for under & overflow here
            {
            yyerror("stack underflow. aborting...");  //note lower case 's'
            return 1;
            }
          yyn = yysindex[state_peek(0)];
          if ((yyn != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
            if (yydebug)
              debug("state "+state_peek(0)+", error recovery shifting to state "+yytable[yyn]+" ");
            yystate = yytable[yyn];
            state_push(yystate);
            val_push(yylval);
            doaction=false;
            break;
            }
          else
            {
            if (yydebug)
              debug("error recovery discarding state "+state_peek(0)+" ");
            if (stateptr<0)   //check for under & overflow here
              {
              yyerror("Stack underflow. aborting...");  //capital 'S'
              return 1;
              }
            state_pop();
            val_pop();
            }
          }
        }
      else            //discard this token
        {
        if (yychar == 0)
          return 1; //yyabort
        if (yydebug)
          {
          yys = null;
          if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
          if (yys == null) yys = "illegal-symbol";
          debug("state "+yystate+", error recovery discards token "+yychar+" ("+yys+")");
          }
        yychar = -1;  //read another
        }
      }//end error recovery
    }//yyn=0 loop
    if (!doaction)   //any reason not to proceed?
      continue;      //skip action
    yym = yylen[yyn];          //get count of terminals on rhs
    if (yydebug)
      debug("state "+yystate+", reducing "+yym+" by rule "+yyn+" ("+yyrule[yyn]+")");
    if (yym>0)                 //if count of rhs not 'nil'
      yyval = val_peek(yym-1); //get current semantic value
    yyval = dup_yyval(yyval); //duplicate yyval if ParserVal is used as semantic value
    switch(yyn)
      {
//########## USER-SUPPLIED ACTIONS ##########
case 4:
//#line 49 "P6.y"
{yyval = val_peek(1);}
break;
case 5:
//#line 50 "P6.y"
{yyval = val_peek(0);}
break;
case 6:
//#line 51 "P6.y"
{yyval = val_peek(2);}
break;
case 7:
//#line 52 "P6.y"
{yyval = val_peek(1);}
break;
case 8:
//#line 55 "P6.y"
{				
				yyval = new ParserVal(maquina.agregarOperacion("varPush_Eval")); 
				maquina.agregar(val_peek(0).sval);
			}
break;
case 9:
//#line 59 "P6.y"
{
				yyval = new ParserVal(maquina.agregarOperacion("constPush"));
				maquina.agregar(val_peek(0).dval);
			}
break;
case 10:
//#line 63 "P6.y"
{
				matrizAux = new Matriz(auxiliar);
				yyval = new ParserVal(maquina.agregarOperacion("constPush"));
       			maquina.agregar(matrizAux);
       			maquina.agregarOperacion("varPush");
		        maquina.agregar(val_peek(7).sval);
		        maquina.agregarOperacion("asignar");
		        maquina.agregarOperacion("varPush_Eval"); 
				maquina.agregar(val_peek(7).sval);
			}
break;
case 11:
//#line 73 "P6.y"
{
				yyval = new ParserVal(val_peek(0).ival);
				maquina.agregarOperacion("varPush");
		        maquina.agregar(val_peek(2).sval);
		        maquina.agregarOperacion("asignar");
		        maquina.agregarOperacion("varPush_Eval"); 
				maquina.agregar(val_peek(2).sval);
			}
break;
case 12:
//#line 81 "P6.y"
{
				yyval = new ParserVal(val_peek(2).ival);
				maquina.agregarOperacion("multiplicar");
			}
break;
case 13:
//#line 85 "P6.y"
{
				yyval = new ParserVal(val_peek(2).ival);
				maquina.agregarOperacion("sumar");
			}
break;
case 14:
//#line 89 "P6.y"
{
				yyval = new ParserVal(val_peek(2).ival);
				maquina.agregarOperacion("restar");
			}
break;
case 15:
//#line 93 "P6.y"
{
				yyval = new ParserVal(val_peek(1).ival);
			}
break;
case 16:
//#line 96 "P6.y"
{
				 maquina.agregarOperacion("comparar");
				 yyval = val_peek(2);
			}
break;
case 17:
//#line 100 "P6.y"
{
				 maquina.agregarOperacion("compararNot");
				 yyval = val_peek(2);
			}
break;
case 18:
//#line 104 "P6.y"
{
				 maquina.agregarOperacion("menor");
				 yyval = val_peek(2);
			}
break;
case 19:
//#line 108 "P6.y"
{
				 maquina.agregarOperacion("menorIgual");
				 yyval = val_peek(2);
			}
break;
case 20:
//#line 112 "P6.y"
{
				 maquina.agregarOperacion("mayor");
				 yyval = val_peek(2);
			}
break;
case 21:
//#line 116 "P6.y"
{
				 maquina.agregarOperacion("mayorIgual");
				 yyval = val_peek(2);
			}
break;
case 22:
//#line 120 "P6.y"
{
				maquina.agregarOperacion("and");
				 yyval = val_peek(2);
			}
break;
case 23:
//#line 124 "P6.y"
{
				maquina.agregarOperacion("or");
				 yyval = val_peek(2);
			}
break;
case 24:
//#line 128 "P6.y"
{
				maquina.agregarOperacion("negar");
				yyval = val_peek(0);
			}
break;
case 25:
//#line 132 "P6.y"
{ 
				yyval = new ParserVal(val_peek(1).ival);
      			maquina.agregar((Funcion)(val_peek(3).obj));
			}
break;
case 26:
//#line 136 "P6.y"
{ yyval = val_peek(0); maquina.agregarOperacion("_return"); }
break;
case 27:
//#line 138 "P6.y"
{ yyval = new ParserVal(maquina.agregarOperacion("push_parametro")); maquina.agregar((int)val_peek(0).ival); }
break;
case 28:
//#line 140 "P6.y"
{ yyval = new ParserVal(maquina.agregarOperacionEn("invocar",(val_peek(3).ival))); maquina.agregar(null); }
break;
case 30:
//#line 144 "P6.y"
{yyval = val_peek(0); maquina.agregar("Limite");}
break;
case 31:
//#line 145 "P6.y"
{yyval = val_peek(2); maquina.agregar("Limite");}
break;
case 32:
//#line 148 "P6.y"
{yyval = new ParserVal(maquina.agregarOperacion("nop"));}
break;
case 33:
//#line 151 "P6.y"
{
				yyval = val_peek(13);
				maquina.agregar(val_peek(7).ival, val_peek(13).ival + 1);
				maquina.agregar(val_peek(2).ival, val_peek(13).ival + 2);
				maquina.agregar(maquina.numeroDeElementos() - 1, val_peek(13).ival + 3);
			}
break;
case 34:
//#line 157 "P6.y"
{
				yyval = val_peek(10);
				maquina.agregar(val_peek(4).ival, val_peek(10).ival + 1);
				maquina.agregar(val_peek(1).ival, val_peek(10).ival + 2);
				maquina.agregar(maquina.numeroDeElementos() - 1, val_peek(10).ival + 3);
			}
break;
case 35:
//#line 163 "P6.y"
{
				yyval = val_peek(9);
				maquina.agregar(val_peek(3).ival, val_peek(9).ival + 1);
				maquina.agregar(val_peek(0).ival, val_peek(9).ival + 2);
			}
break;
case 36:
//#line 168 "P6.y"
{
				yyval = val_peek(15);
				maquina.agregar(val_peek(10).ival, val_peek(15).ival + 1);
				maquina.agregar(val_peek(7).ival, val_peek(15).ival + 2);
				maquina.agregar(val_peek(3).ival, val_peek(15).ival + 3);
				maquina.agregar(val_peek(0).ival, val_peek(15).ival + 4);
			}
break;
case 39:
//#line 179 "P6.y"
{ maquina.agregarOperacion("declaracion"); }
break;
case 40:
//#line 181 "P6.y"
{ maquina.agregarOperacion("declaracion"); }
break;
case 41:
//#line 184 "P6.y"
{yyval = new ParserVal(maquina.agregar(val_peek(0).sval));}
break;
case 42:
//#line 187 "P6.y"
{maquina.agregar(null);}
break;
case 43:
//#line 190 "P6.y"
{yyval = new ParserVal(maquina.agregarOperacion("stop"));}
break;
case 44:
//#line 193 "P6.y"
{
			yyval = new ParserVal(maquina.agregarOperacion("_if_then_else"));
	        maquina.agregarOperacion("stop");/*then*/
	        maquina.agregarOperacion("stop");/*else*/
	        maquina.agregarOperacion("stop");/*siguiente comando*/
		}
break;
case 45:
//#line 201 "P6.y"
{
			yyval = new ParserVal(maquina.agregarOperacion("_while"));
	        maquina.agregarOperacion("stop");/*cuerpo*/
	        maquina.agregarOperacion("stop");/*final*/
		}
break;
case 46:
//#line 208 "P6.y"
{
			yyval = new ParserVal(maquina.agregarOperacion("_for"));
	        maquina.agregarOperacion("stop");/*condicion*/
	        maquina.agregarOperacion("stop");/*instrucción final*/
	        maquina.agregarOperacion("stop");/*cuerpo*/
	        maquina.agregarOperacion("stop");/*final*/
		}
break;
case 47:
//#line 216 "P6.y"
{ yyval = new ParserVal(maquina.agregarOperacion("nop"));}
break;
case 48:
//#line 217 "P6.y"
{yyval = val_peek(0);}
break;
case 49:
//#line 218 "P6.y"
{yyval = val_peek(2);}
break;
case 50:
//#line 221 "P6.y"
{i = 0; j = 0; auxiliar = new double[(int)val_peek(0).dval][(int)val_peek(0).dval];}
break;
case 51:
//#line 224 "P6.y"
{j = 0; i++;}
break;
case 52:
//#line 225 "P6.y"
{ i++; j = 0;}
break;
case 53:
//#line 228 "P6.y"
{auxiliar[i][j] = val_peek(0).dval; j++;}
break;
case 54:
//#line 229 "P6.y"
{auxiliar[i][j] = val_peek(0).dval; j++;}
break;
//#line 966 "Parser.java"
//########## END OF USER-SUPPLIED ACTIONS ##########
    }//switch
    //#### Now let's reduce... ####
    if (yydebug) debug("reduce");
    state_drop(yym);             //we just reduced yylen states
    yystate = state_peek(0);     //get new state
    val_drop(yym);               //corresponding value drop
    yym = yylhs[yyn];            //select next TERMINAL(on lhs)
    if (yystate == 0 && yym == 0)//done? 'rest' state and at first TERMINAL
      {
      if (yydebug) debug("After reduction, shifting from state 0 to state "+YYFINAL+"");
      yystate = YYFINAL;         //explicitly say we're done
      state_push(YYFINAL);       //and save it
      val_push(yyval);           //also save the semantic value of parsing
      if (yychar < 0)            //we want another character?
        {
        yychar = yylex();        //get next character
        if (yychar<0) yychar=0;  //clean, if necessary
        if (yydebug)
          yylexdebug(yystate,yychar);
        }
      if (yychar == 0)          //Good exit (if lex returns 0 ;-)
         break;                 //quit the loop--all DONE
      }//if yystate
    else                        //else not done yet
      {                         //get next state and push, for next yydefred[]
      yyn = yygindex[yym];      //find out where to go
      if ((yyn != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn]; //get new state
      else
        yystate = yydgoto[yym]; //else go to new defred
      if (yydebug) debug("after reduction, shifting from state "+state_peek(0)+" to state "+yystate+"");
      state_push(yystate);     //going again, so push state & val...
      val_push(yyval);         //for next action
      }
    }//main loop
  return 0;//yyaccept!!
}
//## end of method parse() ######################################



//## run() --- for Thread #######################################
/**
 * A default run method, used for operating this parser
 * object in the background.  It is intended for extending Thread
 * or implementing Runnable.  Turn off with -Jnorun .
 */
public void run()
{
  yyparse();
}
//## end of method run() ########################################



//## Constructors ###############################################
/**
 * Default constructor.  Turn off with -Jnoconstruct .

 */
public Parser()
{
  //nothing to do
}


/**
 * Create a parser, setting the debug to true or false.
 * @param debugMe true for debugging, false for no debug.
 */
public Parser(boolean debugMe)
{
  yydebug=debugMe;
}
//###############################################################



}
//################### END OF CLASS ##############################
