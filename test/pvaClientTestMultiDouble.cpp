/*pvaClientTestMultiDouble.cpp */
/**
 * Copyright - See the COPYRIGHT that is included with this distribution.
 * EPICS pvData is distributed subject to a Software License Agreement found
 * in file LICENSE that is included with this distribution.
 */
/**
 * @author mrk
 */

/* Author: Marty Kraimer */

#include <iostream>

#include <pv/pvaClientMultiDouble.h>
#include <epicsUnitTest.h>
#include <testMain.h>

using namespace std;
using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace epics::pvaClient;


static void testGood(PvaClientPtr const &pvaClient)
{
    bool isOk = true;
    cout << "\nstarting testGood\n";
    try {
        PvaClientPtr pvaClient(PvaClient::create());
        size_t num = 5;
        shared_vector<string> channelNames(num);
        channelNames[0] = "exampleDouble01";
        channelNames[1] = "exampleDouble02";
        channelNames[2] = "exampleDouble03";
        channelNames[3] = "exampleDouble04";
        channelNames[4] = "exampleDouble05";
        PVStringArrayPtr pvNames =
            getPVDataCreate()->createPVScalarArray<PVStringArray>();
        pvNames->replace(freeze(channelNames));
        PvaClientMultiDoublePtr multiDouble(PvaClientMultiDouble::create(pvaClient,pvNames));
        shared_vector<double> data = multiDouble->get();
        cout << "initial " << data << endl;
        for(size_t i=0; i<num; ++i) data[i] = data[i] + 1.1;
        multiDouble->put(data);
        data =  multiDouble->get();
        cout << "final " << data << endl;
    } catch (std::runtime_error e) {
        cout << "exception " << e.what() << endl;
        isOk = false;
    }
    testOk(isOk==true,"all channels double");
}

static void testGoodMixed(PvaClientPtr const &pvaClient)
{
    bool isOk = true;
    cout << "\nstarting testGoodMixed\n";
    try {
        PvaClientPtr pvaClient(PvaClient::create());
        size_t num = 5;
        shared_vector<string> channelNames(num);
        channelNames[0] = "exampleByte";
        channelNames[1] = "exampleShort";
        channelNames[2] = "exampleInt";
        channelNames[3] = "exampleFloat";
        channelNames[4] = "exampleDouble";
        PVStringArrayPtr pvNames =
            getPVDataCreate()->createPVScalarArray<PVStringArray>();
        pvNames->replace(freeze(channelNames));
        PvaClientMultiDoublePtr multiDouble(PvaClientMultiDouble::create(pvaClient,pvNames));
        shared_vector<double> data = multiDouble->get();
        cout << "initial " << data << endl;
        for(size_t i=0; i<num; ++i) data[i] = data[i] + 1.1;
        multiDouble->put(data);
        data =  multiDouble->get();
        cout << "final " << data << endl;
    } catch (std::runtime_error e) {
        cout << "exception " << e.what() << endl;
        isOk = false;
    }
    testOk(isOk==true,"channels mixed type");
}

static void testChannelNotExist(PvaClientPtr const &pvaClient)
{
    bool isOk = true;
    cout << "\nstarting testChannelNotExist\n";
    try {
        PvaClientPtr pvaClient(PvaClient::create());
        size_t num = 5;
        shared_vector<string> channelNames(num);
        channelNames[0] = "exampleDouble01";
        channelNames[1] = "exampleDouble02";
        channelNames[2] = "exampleDouble03";
        channelNames[3] = "NoneExistChannel";
        channelNames[4] = "exampleDouble05";
        PVStringArrayPtr pvNames =
            getPVDataCreate()->createPVScalarArray<PVStringArray>();
        pvNames->replace(freeze(channelNames));
        PvaClientMultiDoublePtr multiDouble(PvaClientMultiDouble::create(pvaClient,pvNames));
        shared_vector<double> data = multiDouble->get();
        cout << "initial " << data << endl;
        for(size_t i=0; i<num; ++i) data[i] = data[i] + 1.1;
        multiDouble->put(data);
        data =  multiDouble->get();
        cout << "final " << data << endl;
    } catch (std::runtime_error e) {
        cout << "exception " << e.what() << endl;
        isOk = false;
    }
    testOk(isOk==false,"channel not exist");
}

static void testNonNumeric(PvaClientPtr const &pvaClient)
{
    bool isOk = true;
    cout << "\nstarting testNonNumeric\n";
    try {
        PvaClientPtr pvaClient(PvaClient::create());
        size_t num = 5;
        shared_vector<string> channelNames(num);
        channelNames[0] = "exampleDouble01";
        channelNames[1] = "exampleDouble02";
        channelNames[2] = "exampleDouble03";
        channelNames[3] = "exampleDouble04";
        channelNames[4] = "exampleDouble05Array";
        PVStringArrayPtr pvNames =
            getPVDataCreate()->createPVScalarArray<PVStringArray>();
        pvNames->replace(freeze(channelNames));
        PvaClientMultiDoublePtr multiDouble(PvaClientMultiDouble::create(pvaClient,pvNames));
        shared_vector<double> data = multiDouble->get();
        cout << "initial " << data << endl;
        for(size_t i=0; i<num; ++i) data[i] = data[i] + 1.1;
        multiDouble->put(data);
        data =  multiDouble->get();
        cout << "final " << data << endl;
    } catch (std::runtime_error e) {
        cout << "exception " << e.what() << endl;
        isOk = false;
    }
    testOk(isOk==false,"channel not numeric");
}

MAIN(pvaClientTestMultiDouble)
{
    cout << "\nstarting pvaClientTestMultiDouble\n";
    testPlan(4);
    PvaClientPtr pvaClient = PvaClient::create();
    testGood(pvaClient);
    testGoodMixed(pvaClient);
    testChannelNotExist(pvaClient);
    testNonNumeric(pvaClient);
    cout << "done\n";
    return 0;
}
