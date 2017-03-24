/**
 * Copyright 2015-2017 MICRORISC s.r.o.
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

#ifndef DPALIBRARY_DPALIBRARYDEMO_H
#define DPALIBRARY_DPALIBRARYDEMO_H

#include "IChannel.h"
#include "DpaTransactionTask.h"

/**
* Demo app for testing DPA library.
*
* @author Radek Kuchta, Jaroslav Kadlec
* @author Frantisek Mikulu, Rostislav Spinar
*/

class DpaLibraryDemo {
public:

  enum LedColor {
    kLedRed,
    kLedGreen
  };

  DpaLibraryDemo(IChannel* communicationInterface);
  virtual ~DpaLibraryDemo();
  void start();

private:
  IChannel* m_dpaInterface;
  DpaHandler* m_dpaHandler;

  // new approach
  void pulseLedRDpaTransaction(uint16_t address);
  void readTemperatureDpaTransaction(uint16_t address);

  void pulseLed(uint16_t address, LedColor color);
  void readTemperature(uint16_t address);
  void executeCommand(DpaMessage& message);
  void unexpectedMessage(const DpaMessage& message);
};

#endif //DPALIBRARY_DPALIBRARYDEMO_H