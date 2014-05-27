<?hh // strict
namespace Fastuc\Services\Paypal;

class ButtonTest extends \PHPUnit_Framework_TestCase
{
	public function testUrl()
	{
		$button = new Button( 'Book', 45 );
		$this->assertContains( 'www.paypal.com', $button->getUrl() );

		$button->setSandbox( true );
		$this->assertContains( 'www.sandbox.paypal.com', $button->getUrl() );

		$button->setReturnUrl( 'http://web/return.php' );
		$this->assertEquals( 'http://web/return.php', $button->getReturnUrl() );

		$button->setCancelReturnUrl( 'http://web/cancelReturn.php' );
		$this->assertEquals( 'http://web/return.php', $button->getReturnUrl() );

		$button->setNotifyUrl( 'http://web/notify.php' );
		$this->assertEquals( 'http://web/notify.php', $button->getNotifyUrl() );
	}
}

