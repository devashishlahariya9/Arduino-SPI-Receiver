#include<stdint.h>
#include <SPI.h>

#define SPI_SCK 13
#define SPI_MISO 12
#define SPI_MOSI 11
#define SPI_SS 10

char data;

void SPI_SlaveInit()
{
  pinMode(SCK, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT);
  pinMode(SS, INPUT);

  SPCR = (1 << SPE);
}

char SPI_SlaveReceive()
{
  while (!(SPSR & (1 << SPIF)));

  return SPDR;
}

void setup()
{
  Serial.begin(9600);
  SPI_SlaveInit();
  Serial.println("SLAVE INITIALIZED SUCCESSFULLY!");
}

void loop()
{
  Serial.println("WAITING FOR SS TO GO LOW...");
  while(digitalRead(SS));
  data = SPI_SlaveReceive();
  Serial.print("RECEIVED DATA: ");
  Serial.println(data);
}
