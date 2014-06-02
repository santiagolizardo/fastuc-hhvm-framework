<?hh // strict
namespace Fastuc\Html\Field;

class Button extends \Fastuc\Html\InputField
{
	public function __construct( $name, $value = null )
	{
		parent::__construct( 'button', $name, $value );
	}
}

