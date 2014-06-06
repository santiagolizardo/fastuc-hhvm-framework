<?hh // strict
namespace Fastuc\Cache;

class VolatileTest extends \PHPUnit_Framework_TestCase
{
	/**
	 * @var \Fastuc\Cache\Volatile
	 */
	private $cache;

	public function setUp()
	{
		$this->cache = new Volatile( array() );
	}

	public function tearDown()
	{
		unset( $this->cache );
	}

	public function testInheritance()
	{
		$this->assertInstanceOf( '\Fastuc\Cache\ICache', $this->cache );
	}

	public function testConfigArgument()
	{
		$backend = $this->getMock( '\Memcached', [ 'set', 'get', 'delete' ] );
		$backend->expects( $this->once() )
			->method( 'set' )
			->with( 'ns_foo', 'bar', 0 );
		$backend->expects( $this->once() )
			->method( 'get' )
			->with( 'ns_foo' )
			->will( $this->returnValue( 'bar' ) );
		$backend->expects( $this->once() )
			->method( 'delete' )
			->with( 'ns_foo' )
			->will( $this->returnValue( true ) );

		$this->cache->setBackend( $backend );
		$this->cache->setNamespace( 'ns_' );
		$this->cache->set( 'foo', 'bar' );
		$this->assertEquals( 'bar', $this->cache->get( 'foo' ) );
		$this->cache->delete( 'foo' );
	}
}

