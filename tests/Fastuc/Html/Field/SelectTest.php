<?hh // strict
namespace Fastuc\Html\Field;

class SelectTest extends \PHPUnit_Framework_TestCase
{
	public function testOptions()
	{
		$select = new Select( 'countries' );
		$select->addOption( 'Spain', 'ES' );

		$this->assertEquals( 'countries', $select->getName() );
		$this->assertContains( 'value="ES"', $select->__toString() );
	}
}

