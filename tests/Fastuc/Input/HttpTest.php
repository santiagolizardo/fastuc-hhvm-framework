<?hh // strict
namespace Fastuc\Input;

class HttpTest extends \PHPUnit_Framework_TestCase
{
	public function testInvalidConstructorArgument()
	{
		$this->setExpectedException( '\InvalidArgumentException', 'Method "read" is invalid'  );

		new Http( 'read' );
	}

	public function testValidConstructorArgumentInLowercase()
	{
		$http = new Http( 'get' );
		$this->assertEquals( 'GET', $http->getMethod() );
	}
}

