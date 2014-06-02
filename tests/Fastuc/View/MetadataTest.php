<?hh // strict
namespace Fastuc\View;

class MetadataTest extends \PHPUnit_Framework_TestCase
{
	public function testFillPage()
	{
		$view = new Page;
		$this->assertNull( $view->getTitle() );

		$params = Map<string, mixed> { 'itemName' => 'you' };
		Metadata::fillView( $view, 'profile/view', $params );

		$this->assertEquals( 'Information about you', $view->getTitle() );
	}
}

