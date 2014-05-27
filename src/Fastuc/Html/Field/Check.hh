<?hh // strict
namespace Fastuc\Html\Field;

/**
 * @todo Rename to Checkbox
 */
class Check extends \Fastuc\Html\InputField
{
	public function __construct( $name, $value = null )
	{
		parent::__construct( 'checkbox', $name, $value );
	}

	public function setChecked( $checked )
	{
		if( $checked )
		{
			$this->el->setAttribute( 'checked', 'checked' );
		} else {
			$this->el->removeAttribute( 'checked' );
		}
	}

	public function isChecked()
	{
		return $this->el->hasAttribute( 'checked' );
	}
}

