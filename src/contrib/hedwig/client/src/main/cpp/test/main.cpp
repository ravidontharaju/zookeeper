/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "../lib/channel.h"
#include "../lib/util.h"
#include <hedwig/protocol.h>
#include <hedwig/callback.h>
#include <iostream>
#include <log4cpp/PropertyConfigurator.hh>
#include <log4cpp/Category.hh>
#include "servercontrol.h"

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>

int main( int argc, char **argv)
{
  try {
    log4cpp::PropertyConfigurator::configure("../log4cpp.conf");
  } catch (log4cpp::ConfigureFailure &e) {
    std::cerr << "log4cpp configuration failure while loading : " << e.what() << std::endl;
  } catch (std::exception &e) {
    std::cerr << "exception caught while configuring log4cpp via : " << e.what() << std::endl;
  } catch (...) {
    std::cerr << "unknown exception while configuring log4cpp vi'." << std::endl;
  }
  std::string testPath = (argc > 2) ? std::string(argv[2]) : "";

  CppUnit::TextTestRunner runner;

  if (argc > 1) {
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry(argv[1]);
    
    runner.addTest( registry.makeTest() );
  } else {
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry("*");
    registry.addRegistry("Util");
    registry.addRegistry("Subscribe");
    registry.addRegistry("Publish"); 
    registry.addRegistry("PubSub");
    
    runner.addTest( registry.makeTest() );
  }
  int ret =  runner.run(testPath);
  google::protobuf::ShutdownProtobufLibrary();
  
  log4cpp::Category::shutdown();
  
  return ret;
}
