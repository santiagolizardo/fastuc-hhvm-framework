<?hh // strict
namespace Fastuc\Web;

class PaginatorTest extends \PHPUnit_Framework_TestCase
{
	public function testDefaults()
	{
		$paginator = new Paginator;
		$this->assertEquals( 0, $paginator->getNumItems() );
		$this->assertEquals( 0, $paginator->getNumPages() );
		$this->assertEquals( 0, $paginator->getSelectedPage() );
		$this->assertEquals( array(), $paginator->getPages() );
		$this->assertEquals( '?page=26', $paginator->createPageUrl( 26 ) );
	}

	/**
	 * @return array
	 */
	public function dataProviderForPages()
	{
		return array(
			'One page' => array(
				10,
				array(
					array(
						'selected' => true,
						'number' => 1,
						'url' => '?page=0',
					),
				),
			),
			'Two pages' => array(
				19,
				array(
					array(
						'selected' => true,
						'number' => 1,
						'url' => '?page=0',
					),
					array(
						'selected' => false,
						'number' => 2,
						'url' => '?page=1',
					),
				),
			),
		);
	}

	/**
	 * @dataProvider dataProviderForPages
	 */
	public function testPages( $numItems, array $pages )
	{
		$paginator = new Paginator;
		$paginator->setNumItems( $numItems );
		$this->assertEquals( $pages, $paginator->getPages() );
	}
}

