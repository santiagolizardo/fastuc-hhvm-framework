<?hh // strict
namespace Fastuc\Html\Field;

class Email extends \Fastuc\Html\InputField
{
	public function __construct( $name, $value = null )
	{
		parent::__construct( 'email', $name, $value );
	}
}

