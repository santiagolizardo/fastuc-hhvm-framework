<?hh // strict
namespace Fastuc\Cache;

class DiskTest extends \PHPUnit_Framework_TestCase
{
	/**
	 * @var \Fastuc\Cache\Disk
	 */
	private $cache;

	public function setUp()
	{
		$this->cache = new Disk;
		$this->cache->setDirectory( __DIR__ );
	}

	public function testInheritance()
	{
		$this->assertInstanceOf( '\Fastuc\Cache\ICache', $this->cache );
	}

	public function testDirectorySetting()
	{
		$this->assertEquals( __DIR__, $this->cache->getDirectory() );
		$this->cache->setDirectory( '/tmp' );
		$this->assertEquals( '/tmp', $this->cache->getDirectory() );
	}

	public function testInitialization()
	{
		$this->assertEquals( 3600, $this->cache->getExpirationTime() );
		$this->assertNotNull( $this->cache->getDirectory(), 'Default cache directory should be the current dir' );
	}

	public function testInvalidCache()
	{
		$this->assertFalse( $this->cache->check( 'does-not-exist' ) );
		$this->assertNull( $this->cache->get( 'does-not-exist' ) );
	}

	public function testSetAndGet()
	{
		$news = 'bank, politics, games';
		$this->cache->set( 'news', $news );
		$this->assertEquals( $news, $this->cache->get( 'news' ) );
	}
}

