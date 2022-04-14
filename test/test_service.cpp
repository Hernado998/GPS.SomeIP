#include <iostream>
#include "gpsdconnector.h"
#include "gpsstorage.h"

#include "gtest/gtest.h"

class ServiceTest : public testing::Test
{
public:
	ServiceTest() = default;
	
protected:
	void SetUp() override;
	void TearDown() override;
	
	GpsStorage* m_storage;
	GpsdConnector* m_connector;
	
	
};

/*
 *  TEST LIST
 *   - get coordinates from nmea string
 *   - get fix from nmea string
 */

TEST_F(ServiceTest, InitialValues)
{
	EXPECT_EQ( m_storage->getLatitude(), 0 );
	EXPECT_EQ( m_storage->getLongitude(), 0 );
	EXPECT_FALSE( m_storage->getFix() );
}

// Get coordinates from NMEA string
TEST_F(ServiceTest, ComputeCoordinates)
{
	m_connector->onSentenceReceived("$GPRMC,062352.000,A,4507.15643,N,00738.21815,E,61.9,65.5,050811,0.0,W*7F");
	
	EXPECT_NEAR( m_storage->getLatitude(), 45.1193, 0.1 );
	EXPECT_NEAR( m_storage->getLongitude(), 7.63697, 0.1 );
}

// Get coordinates from NMEA string
TEST_F(ServiceTest, ComputeFix)
{
	m_connector->onSentenceReceived("$GPRMC,062352.000,A,4507.15643,N,00738.21815,E,61.9,65.5,050811,0.0,W*7F");
	
	EXPECT_TRUE( m_storage->getFix() );
}

void ServiceTest::SetUp()
{
	m_storage = new GpsStorage();
	m_connector = new GpsdConnector(m_storage);
	m_connector->init();
}

void ServiceTest::TearDown()
{
	delete m_connector;
	delete m_storage;
}
