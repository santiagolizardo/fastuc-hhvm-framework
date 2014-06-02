<?hh // strict
namespace Fastuc\Seo;

class SitemapIndexTest extends \PHPUnit_Framework_TestCase
{
	public function testRules()
	{
		$sitemapIndex = new SitemapIndex;
		$this->assertEmpty( $sitemapIndex->getSitemaps() );
		
		$sitemapIndex->addSitemap( 'http://www.testing.com' );

		$sitemaps = array(
			array( 'location' => 'http://www.testing.com' )
		);
		$this->assertEquals( $sitemaps, $sitemapIndex->getSitemaps() );
	}
}

