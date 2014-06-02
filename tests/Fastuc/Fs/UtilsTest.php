<?hh // strict
namespace Fastuc\Fs;

class UtilsTest extends \PHPUnit_Framework_TestCase
{
	/**
	 * @return array
	 */
	public function dataProviderForFormatSize()
	{
		return array(
			array( 0, '0 B' ),
			array( 1000, '1000 B' ),
			array( 2000, '1.95 KB' ),
			array( 10241024, '9.77 MB' ),
		);
	}

	/**
	 * @dataProvider dataProviderForFormatSize
	 */
	public function testFormatSize( $bytes, $expected )
	{
		$this->assertEquals( $expected, Utils::formatSize( $bytes ) );
	}
}


