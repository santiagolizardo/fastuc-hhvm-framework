<?hh // strict
namespace Fastuc\Input;

class FilterTest extends \PHPUnit_Framework_TestCase
{
	public function testFilters()
	{
		$input = 'i am a <script>alert(\'hacker\');</script>';
		$output = 'i am a &lt;script&gt;alert(\'hacker\');&lt;/script&gt;';

		$params = new Http( 'CUSTOM' );
		$params->setParam( 'foo', $input );

		$filter = new Filter( $params );

		$this->assertEquals( $output, $filter->getString( 'foo', array(), null, array( 'htmlentities' ) ) );
	}
}

