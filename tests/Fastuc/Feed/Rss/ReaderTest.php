<?hh // strict
namespace Fastuc\Feed\Rss;

class ReaderTest extends \PHPUnit_Framework_TestCase
{
	public function testParsing()
	{
		$reader = new Reader( __DIR__ . '/sample-rss.xml' );
		$items = $reader->getItems();
		$this->assertEquals( 10, count( $items ) );
	}
}

