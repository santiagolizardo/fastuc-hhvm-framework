<?hh // strict
namespace Fastuc\Utils;

class RandomTest extends \PHPUnit_Framework_TestCase
{
	public function testRandomString()
	{
		$this->assertEquals( 5, strlen( Random::createRandomString( 5 ) ) );
	}
}

