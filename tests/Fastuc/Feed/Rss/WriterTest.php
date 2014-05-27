<?hh // strict
namespace Fastuc\Feed\Rss;

class WriterTest extends \PHPUnit_Framework_TestCase
{
	public function testFeedGeneration()
	{
		$writer = new Writer;
		$writer->setTitle( 'Testing RSS writer' );

		$xml = $writer->toXml();

		$this->assertContains( '<title>Testing RSS writer</title>', $xml );
		$this->assertNotEmpty( $xml );
	}
}

