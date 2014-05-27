<?hh // strict
namespace Fastuc\Utils;

class NetworkTest extends \PHPUnit_Framework_TestCase
{
	/**
	 * @return array
	 */
	public function dataProviderForCurrentUrl()
	{
		return array(
			array(
				array(
					'HTTPS' => '',
					'HTTP_HOST' => 'localaddr',
					'SERVER_PORT' => '443',
					'REQUEST_URI' => '/foobar.html',
				),
				'http://localaddr:443/foobar.html'
			),
			array(
				array(
					'HTTPS' => 's',
					'HTTP_HOST' => 'localaddr',
					'SERVER_PORT' => '80',
					'REQUEST_URI' => '/foobar.html',
				),
				'https://localaddr/foobar.html'
			),
			array(
				array(
					'HTTPS' => '',
					'HTTP_HOST' => 'localaddr',
					'SERVER_PORT' => '80',
					'REQUEST_URI' => '/foobar.html',
				),
				'http://localaddr/foobar.html'
			),
		);
	}

	/**
	 * @dataProvider dataProviderForCurrentUrl
	 */
	public function testGetCurrentUrl( array $serverVars, $expectedUrl )
	{
		$this->assertEquals( $expectedUrl, Network::getCurrentUrl( $serverVars ) );
	}

	/**
	 * @return array
	 */
	public function dataProviderForClientIp()
	{
		return array(
			array(
				array(), null,
			),
			array(
				array( 'HTTP_CLIENT_IP' => '127.0.0.1' ),
				'127.0.0.1',
			),
			array(
				array( 'HTTP_X_FORWARDED_FOR' => '8.3.2.1' ),
				'8.3.2.1',
			),
			array(
				array( 'REMOTE_ADDR' => '127.001' ),
				null,
			),
		);
	}


	/**
	 * @dataProvider dataProviderForClientIp
	 */
	public function testClientIp( array $serverVars, $expectedIp )
	{
		$this->assertEquals( $expectedIp, Network::getClientIp( $serverVars ) );
	}
}

