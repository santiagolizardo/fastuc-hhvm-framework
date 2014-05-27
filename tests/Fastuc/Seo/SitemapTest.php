<?hh // strict
namespace Fastuc\Seo;

class SitemapTest extends \PHPUnit_Framework_TestCase
{
	private $sitemap;

	public function setUp()
	{
		$this->sitemap = new Sitemap;
	}

	public function tearDown()
	{
		unset( $this->sitemap );
	}

	public function testRules()
	{
		$this->assertEmpty( $this->sitemap->getUrls() );
		
		$this->sitemap->addUrl( 'http://www.santiagolizardo.com', Sitemap::FREQ_HOURLY, .9 );

		$urls = array(
			array(
				'location' => 'http://www.santiagolizardo.com',
				'changeFrequency' => Sitemap::FREQ_HOURLY,
				'priority' => .9
			)
		);
		$this->assertEquals( $urls, $this->sitemap->getUrls() );
	}

	public function testAddingWrongUrl()
	{
		$this->setExpectedException( '\Exception', 'Invalid frequency: immediately' );

		$this->sitemap->addUrl( 'http://www.now.com', 'immediately', '1.0' );
	}

	public function testStringGeneration()
	{
		$this->sitemap->addUrl( 'http://fastuc.org', Sitemap::FREQ_WEEKLY, .5 );
		$xml = $this->sitemap->dumpToString();

		$this->assertContains( 'xml version="1.0" encoding="utf-8"', $xml );
		$this->assertContains( '<loc>http://fastuc.org</loc>', $xml );
		$this->assertContains( '<priority>0.5</priority>', $xml );
	}

	public function testStringRepresentation()
	{
		$this->assertEquals( '[ Sitemap: urls(0) ]', strval( $this->sitemap ) );
	}
}

