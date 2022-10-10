//#define TERMINAL            //UNCOMENT IF USE TERMINAL SOFT
#define RX8900A_ADRS           0x32
#define SEC_reg                0x00
#define MIN_reg                0x01
#define HOUR_reg               0x02
#define WEEK_reg               0x03
#define DAY_reg                0x04
#define MONTH_reg              0x05
#define YEAR_reg               0x06
#define RAM_reg                0x07
#define MIN_Alarm_reg          0x08
#define HOUR_Alarm_reg         0x09
#define WEEK_DAY_Alarm_reg     0x0A
#define Timer_Counter_0_reg    0x0B
#define Timer_Counter_1_reg    0x0C
#define Extension_Register_reg 0x0D
#define Flag_Register_reg      0x0E
#define Control_Register_reg   0x0F
#define TEMP_reg               0x17
#define Backup_Function_reg    0x18
#define NO_WEEK 0x00
#define SUN 0x01
#define MON 0x02
#define TUE 0x04
#define WED 0x08
#define THU 0x10
#define FRI 0x20
#define SAT 0x40

unsigned char SEC     = 0x00;//0x00-0x59
unsigned char MIN     = 0x00;//0x00-0x59
unsigned char HOUR    = 0x00;//0x00-0x23
unsigned char WEEK    = 0x01;//SUN=0x01,MON=0x02,TUE=0x04,WED=0x08,THU=0x10,FRI=0x20,SAT=0x40
unsigned char DAY     = 0x01;//0x00-0x28～0x31)
unsigned char MONTH   = 0x01;//JUN=0x01,FEB=0x02,MAR=0x03,APR=0x04,MAY=0x05,JUN=0x06,JLY=0x07,AUG=0x08,SEP=0x09,OCT=0x10,NOV=0x11,DEC=0x12
unsigned char YEAR    = 0x021;//0x00-0x99
unsigned char RAM;
unsigned char MIN_Alarm;
unsigned char HOUR_Alarm;
unsigned char WEEK_DAY_Alarm;
unsigned char Timer_Counter_0;
unsigned char Timer_Counter_1;
unsigned char Extension_Register;
unsigned char Flag_Register;
unsigned char Control_Register;
unsigned char TEMP;
float         TEMP_RESULT;
unsigned char Backup_Function;
unsigned char DUMMY;
unsigned char OLD_SEC = 0;
unsigned char OLD_Timer_Counter_0 = 0;

char WEEK_D[7][5] = { "Sun.", "Mon.", "Tue.", "Wed.", "Thu.", "Fri.", "Sat." };

String WEEK_S  = "Sun.Mon.Tue.Wed.Thu.Fri.Sat.";
unsigned char RX_DATA;
unsigned long RX_RESULT;
unsigned char RX_FLAG;
unsigned char DATA_OK_FLAG;
unsigned char BAD_DATA_FLAG;
unsigned char ALARM_BUFFER;
unsigned char str_data[8];
unsigned long WEEK_ALARM_BUFFER;
unsigned int TIMER_VALUE;

enum SYORI_FLAG
{
  TOKEI,
  TOKEI_COUNT,
  ALARM_SET,
  ALARM_ON,
  ALARM_OFF,
  ALARM_STOP,
  TIMER_SET,
  TIMER_START,
  TIMER_COUNT,
  TIMER_STOP,
  TIMER_HALT,
  TIMER_OVER
} SYORI_FLAG;
