<?hh // strict
namespace Fastuc\View;
/*
class PageTest extends \PHPUnit_Framework_TestCase
{
	private $page;

	public function setUp()
	{
		$this->page = new Page;
	}

	public function tearDown()
	{
		unset( $this->page );
	}

	public function notestMediaCollections()
	{
		$this->assertNull( $this->page->getTitle() );
		$this->assertEmpty( $this->page->getStyleSheets() );
		$this->assertTrue( $this->page->getJavaScripts()->isEmpty() );
	}

	public function testLinksAreWellFiltered()
	{
		$this->page->addLink( 'alternate', 'foo.css' );
		$this->page->addLink( 'stylesheet', 'bar.css' );
		$this->page->addLink( 'author', 'someone.html' );

		$styleSheets = array(
			1 => array( 'rel' => 'stylesheet', 'href' => 'bar.css', 'type' => '', 'media' => '', 'title' => '' ),
		);
		$this->assertEquals( $styleSheets, $this->page->getStyleSheets() );
		$this->assertCount( 3, $this->page->getLinks() );
	}

	public function testMetas()
	{
		$this->assertEmpty( $this->page->getMetas() );
		$this->assertNull( $this->page->getMeta( 'missing' ) );

		$this->page->setMeta( 'keywords', 'foo,bar' );
		$this->page->setMeta( 'description', 'a,desc' );
		$this->assertEquals( 'foo,bar', $this->page->getMetaKeywords() );
		$this->assertEquals( 'a,desc', $this->page->getMetaDescription() );

		$metas = array(
			'keywords' => 'foo,bar',
			'description' => 'a,desc',
		);
		$this->assertEquals( $metas, $this->page->getMetas() );
	}
}
 */
