<?hh // strict
namespace Fastuc\Url;

class BaseTest extends \PHPUnit_Framework_TestCase
{
	public function testRouteExistence()
	{
		$url = new Base;
		$this->assertEquals( '/foo/bar', $url->create( 'foo/bar' ) );
	}
}

