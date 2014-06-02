<?hh // strict
namespace Fastuc;

class RegistryTest extends \PHPUnit_Framework_TestCase
{
	/**
	 * @var \Fastuc\Registry
	 */
	private $registry;

	public function setUp()
	{
		$this->registry = Registry::getInstance();
	}

	public function testSingletonInstance()
	{
		$this->assertSame( Registry::getInstance(), $this->registry );
	}

	public function testSettingAndGetting()
	{
		$this->assertFalse( $this->registry->hasParam( 'expensiveCalculation' ) );

		$this->registry->setParam( 'expensiveCalculation', 5 * 5 );

		$this->assertEquals( 25, $this->registry->getParam( 'expensiveCalculation' ) );
	}

	public function testUnsetAndReset()
	{
		$this->registry->setParam( 'foo', 'bar' );
		$this->registry->setParam( 'scott', 'tiger' );
		$this->assertTrue( $this->registry->hasParam( 'foo' ) && $this->registry->hasParam( 'scott' ) );

		$this->registry->unsetParam( 'scott' );
		$this->assertTrue( $this->registry->hasParam( 'foo' ) && !$this->registry->hasParam( 'scott' ) );

		$this->registry->unsetParams();
		$this->assertFalse( $this->registry->hasParam( 'foo' ) || $this->registry->hasParam( 'scott' ) );
	}
}

