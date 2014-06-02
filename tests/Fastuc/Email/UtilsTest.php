<?hh // strict
namespace Fastuc\Email;

class UtilsTest extends \PHPUnit_Framework_Testcase
{
	/**
	 * @return array
	 */
	public function dataProviderForFormatAddress()
	{
		return array(
			array( 'foo@bar', 'foo@bar', null ),
			array( 'foo@bar', 'foo@bar', '' ),
			array( 'Mr. Foo Bar <foo@bar>', 'foo@bar', 'Mr. Foo Bar' ),
		);
	}

	/**
	 * @dataProvider dataProviderForFormatAddress
	 */
	public function testFormatAddress( $expected, $address, $name )
	{
		$this->assertEquals( $expected, Utils::formatAddress( $address, $name ) );
	}
}

