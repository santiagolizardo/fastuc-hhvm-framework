<?hh // strict
namespace Fastuc\Seo;

class RobotsTest extends \PHPUnit_Framework_TestCase
{
	private $robots;

	public function setUp()
	{
		$this->robots = new Robots;
	}

	public function tearDown()
	{
		unset( $this->robots );
	}

	public function testInitialization()
	{
		$this->assertNull( $this->robots->getSitemapUrl() );
		$this->assertEmpty( $this->robots->getRules() );
	}

	public function testStringGeneration()
	{
		$this->robots->setSitemapUrl( 'http://nicesite.com/sitemap.xml' );
		$this->robots->addRule( 'IE', false, '.*' );

		$string = $this->robots->toText();
		$this->assertContains( 'User-agent: IE', $string );
		$this->assertContains( 'Disallow: .*', $string );
		$this->assertContains( 'Sitemap: http://nicesite.com/sitemap.xml', $string );
	}

	public function testObjectStringRepresentation()
	{
		$this->assertEquals( '[ Robots: rules(0), sitemapUrl() ]', strval( $this->robots ) );
	}
}

